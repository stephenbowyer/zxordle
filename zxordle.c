#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <graphics.h>
#include <input.h>
#include <time.h>
#include <zx81.h>
#include <math.h>
#include <string.h>
#include "wordlist.h"

#define VER "0.5"
#define YEAR "2025"
#define NAME "ZXORDLE"

int printStringAt(int8_t y, int8_t x, char *text){
  zx_setcursorpos(y,x);
  return(printf("%s", text));
}

int printCharAt(int8_t y, int8_t x, char text){
  zx_setcursorpos(y,x);
  return(printf("%c", text));
}

char newGetChar(bool block){
  char input;
  if (block)
  {
    in_WaitForNoKey();  
    in_WaitForKey();
  }
  while((input=in_Inkey()))
  {
    if ((input != NULL) && (block))
      in_WaitForNoKey();
    if ((input >= 0x41) && (input <= 0x5A)) // convert uppercase to lowercase
      input += 32;
    return(input);
  }  
}

void animateLogo(int8_t position){
    int8_t ranPos = rand() % 7; // which character to animate
    int8_t ranColour = rand() % 2; // which colour to use
    char* myName = NAME;
    char* myChar = myName[ranPos];
    if (ranColour == 1)
        myChar += 32; // convert to lowercase for black on white
    printCharAt(position, 12+ranPos, myChar);
}

void flashCursor(int8_t y, int8_t x, int8_t colour){
  if (colour == 0)
    printCharAt(y, x, ' ');
  else
    printCharAt(y, x, '@');
}

void displayScore(unsigned long currscore, unsigned long maxscore){
    char scoremsg[32];
    snprintf(scoremsg, sizeof(scoremsg), "%lu/%lu", currscore, maxscore);
    printStringAt(0, 27, "score");
    printStringAt(1, 32-strlen(scoremsg), scoremsg);
}

void menu(){
    int8_t randomSeed = 0;
    zx_cls(); // 32 char screen width
    printStringAt(4,11, "@@@@@@@@@");
    printStringAt(5,11, "@ZXORDLE@");
    printStringAt(6,11, "@@@@@@@@@");
    {
        char versionMsg[32];
        sprintf(versionMsg, "version %s  (%s)", VER, YEAR);
        printStringAt(8,6, versionMsg);
    }
    printStringAt(9,7, "by stephen bowyer");
    printStringAt(10,0, "based on a game by josh wardle");
    printStringAt(13,5, "a word puzzle where six");
    printStringAt(14,2, "attempts are offered to guess");
    printStringAt(15,3, "the hidden five-letter word");
    printStringAt(18,6, "press any key to start");
    zx_slow();
    srand(randomSeed);
    while(true){
        char input = newGetChar(false);
        if (input != NULL){
            printStringAt(5,12, "ZXORDLE");
            clga(0, 16, 64, 24); // clear everything except logo
            scrolluptxt(); scrolluptxt(); scrolluptxt(); scrolluptxt();
            break;
        }
        animateLogo(5);
    }
}

void drawGameScreen(){
    for (int8_t line = 4; line < 17; line++){
      printStringAt(line, 11, "@@@@@@@@@");
    }
}

void drawGameKey(){
    printStringAt(14, 21, "Y correct");
    printStringAt(15, 21, "P misplaced");
    printStringAt(16, 21, "N incorrect");

}

char* selectWord(){
  int words = sizeof(wordlist) / WORDLENGTH;
  int randomIndex = rand() % words; // Get a random word index
  char *selectedWord = (char *)malloc(WORDLENGTH + 1);
  memcpy(selectedWord, wordlist[randomIndex], WORDLENGTH); // Copy randomly chosen word
  selectedWord[WORDLENGTH] = '\0';
  return selectedWord;
}

int queryWords(char *word){
  int8_t attempt = 0;
  char* ordinal[6] = {"first", "second", "third", "fourth", "fifth", "sixth"};
  char upperWord[6];
  printf("word is %s\n", word);
  for (int k = 0; k < 5; k++) {
      upperWord[k] = word[k] - 32; // convert to uppercase
  }
  upperWord[5] = '\0';
  for (int8_t i = 1; i < 7; i++){
    char input[6];
    printStringAt((i*2)+3,13, "     ");
    {
        char attemptMsg[32];
        snprintf(attemptMsg, sizeof(attemptMsg), " please type your %s guess ", ordinal[i-1]);
        printStringAt(20, floor(32-strlen(attemptMsg)), attemptMsg);
    }
    for (int8_t j = 0; j < 5; j++){
        input[j] = '';
        int colour = 1;
        int counter = 0;
        do{
          input[j] = newGetChar(false);
          if (counter++ > 300){
            flashCursor((i*2)+3, j+13, colour);
            colour = 1 - colour;
            counter = 0;
          }
        } while(!((input[j] >= 0x61) && (input[j] <= 0x7A) || (input[j] == 0x0c)));
        in_WaitForNoKey();
        if ((input[j] >= 0x61) && (input[j] <= 0x7A)) // alphabetic characters
          printCharAt((i*2)+3, j+13, input[j]);
        else
          if (input[j] == 0x0c && j > 0){ // rubout / delete
            flashCursor((i*2)+3, j+13, 0); // clear flashing cursor 
            j=j-2;
          }
          else
            j--; // repeat position
    }
    input[5] = '\0'; // null-terminate the string
    if (strcmp(input, word) == 0){
        {
          char attemptMsg[32];
          snprintf(attemptMsg, sizeof(attemptMsg), "%s on your %s attempt", upperWord, ordinal[i-1]);
          clga(0, 38, 64, 6); // clear the bottom of the screen
          printStringAt(19, 8,    "congratulations");
          printStringAt(20, 5, "you correctly guessed");
          printStringAt(21, 2, attemptMsg);
        }
        free(word);
        if (i == 6)
          return(10); // score 10 for sixth attempt
        else
          return(100 - (20 * (i-1))); //score 100 for first attempt, minus 20 for each subsequent attempt
    }else{
      for (int8_t j = 0; j < 5; j++){ // check for correct letters
        if (input[j] == word[j]){
          printCharAt((i*2)+4, j+13, 'Y'); // correctly placed letter
        } else if (strchr(word, input[j]) != NULL) {
          printCharAt((i*2)+4, j+13, 'P'); // present letter
        } else {
          printCharAt((i*2)+4, j+13, 'N'); // absent letter
        }
      }
    }
  }
  {
    char attemptMsg[32];
    snprintf(attemptMsg, sizeof(attemptMsg), "you did not find the word %s", upperWord);
    printStringAt(19, 13, "sorry");
    printStringAt(20, 0, attemptMsg);
    free(word);
  }
  return(0);
}

void main(){
  unsigned long currscore = 0;
  unsigned long maxscore = 0;
    while(true){
        menu();
        drawGameScreen();
        drawGameKey();
        displayScore(currscore, maxscore);
        currscore += queryWords(selectWord());
        maxscore += 100;
        displayScore(currscore, maxscore);
        printStringAt(23, 4, "press any key to restart");
        newGetChar(true);
      }
}