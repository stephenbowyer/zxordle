#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <graphics.h>
#include <input.h>
#include <time.h>
#include <string.h>
#if defined(__ZX81__) || defined(__ZX80__)
  #include <zx81.h>
  #define gotoxy(x,y) zx_setcursorpos(y,x)
#elif defined(__SPECTRUM__)
  #include <arch/zx/spectrum.h>
  #include <conio.h>
  #define scrolluptxt() printCharAt(24,0, ' ')
#endif

#include "wordlist.h"
#include "messages.h"

#define VER "0.5"
#define YEAR "2025"

int printStringAt(int8_t y, int8_t x, char *text){
  gotoxy(x,y);
  return(printf("%s", text));
}

int printCharAt(int8_t y, int8_t x, char text){
  gotoxy(x,y);
  return(printf("%c", text));
}

char newGetChar(bool block){
  char input;
  #if defined(__ZX80__)
    input = fgetc_cons();
    if ((input >= 0x41) && (input <= 0x5A)) // convert uppercase to lowercase
      input += 32;
    return(input);
  #elif defined(__ZX81__) || defined(__SPECTRUM__)
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
  #endif
}

#if defined(__ZX81__) || defined(__SPECTRUM__)
  void animateLogo(int8_t position){
      int8_t ranPos = rand() % 7; // which character to animate
      #if defined(__ZX81__)
        int8_t ranColour = rand() % 2; // which colour to use
      #elif defined(__SPECTRUM__)
        int8_t ranColour = rand() % 4; // which colour to use (0=red, 1=green, 2=yellow, 3=white)
      #endif
      char* myName = MSG_NAME;
      char* myChar = myName[ranPos];
      #if defined(__ZX81__)
        if (ranColour == 1)
          myChar += 32; // convert to lowercase for black on white
        printCharAt(position, 12+ranPos, myChar);
      #elif defined(__SPECTRUM__)
        char animChar[6];
        if (ranColour == 0)
          ranColour = 7;
        else
          ranColour *= 2;
        snprintf(animChar, sizeof(animChar), "\x11%c%c\x11\x07", ranColour, myChar);
        // if (ranColour == 1)
        //   snprintf(animChar, sizeof(animChar), "%s%c%s", DARK, myChar, LIGHT);
        // else
        //   snprintf(animChar, sizeof(animChar), "%c", myChar);
        printStringAt(position, 12+ranPos, animChar);
      #endif
  }
#endif

void flashCursor(int8_t y, int8_t x, int8_t colour){
    if (colour == 0)
      printStringAt(y, x, MSG_EMPTY_SQUARE);
    else
      printStringAt(y, x, MSG_CURSOR);
}

void displayScore(unsigned long currscore, unsigned long maxscore){
    char scoremsg[32];
    snprintf(scoremsg, sizeof(scoremsg), "%lu/%lu", currscore, maxscore);
    printStringAt(0, 27, MSG_SCORE);
    printStringAt(1, 32-strlen(scoremsg), scoremsg);
}

void printLogo(int8_t y, int8_t x){
  char logoMsg[20];
  snprintf(logoMsg, sizeof(logoMsg), "%s%s%s%s", MSG_BLACK_SQUARE, DARK, MSG_NAME, MSG_BLACK_SQUARE);
  printStringAt(y,x, logoMsg);
}

void menu(){
    zx_cls(); // 32 char screen width
    printStringAt(4,11, MSG_BLACK_LINE);
    printLogo(5,11);
    printStringAt(6,11, MSG_BLACK_LINE);
    {
        char versionMsg[32];
        sprintf(versionMsg, "%s %s  (%s)", MSG_VERSION, VER, YEAR);
        printStringAt(8,6, versionMsg);
    }
    printStringAt(9,7, MSG_AUTHOR);
    printStringAt(10,0, MSG_BASED_ON);
    printStringAt(13,5, MSG_DESC1);
    printStringAt(14,2, MSG_DESC2);
    printStringAt(15,3, MSG_DESC3);
    printStringAt(18,6, MSG_START);
    #ifdef __ZX81__
      zx_slow();
    #endif
    int loopCount = 0;
    while(true){
        char input = newGetChar(false);
        loopCount++;
        if (input != NULL){
            printLogo(5,11);
            #if defined(__ZX81__) || defined(__ZX80__)
              clga(0, 16, 64, 24); // clear everything except logo
            #elif defined(__SPECTRUM__)
              clga(0, 60, 250, 100); // clear everything except logo
            #endif
            scrolluptxt(); scrolluptxt(); scrolluptxt(); scrolluptxt();
            srand((unsigned int) time(NULL) + loopCount);
            break;
        }
        #if defined(__ZX81__) || defined(__SPECTRUM__)
          if (loopCount % 20 == 0)
            animateLogo(5);
        #endif
    }
}

void drawGameScreen(){
    for (int8_t line = 4; line < 17; line++){
      printStringAt(line, 11, MSG_BLACK_LINE);
    }
}

void drawGameKey(){
    printStringAt(14, 21, MSG_KEY_Y);
    printStringAt(15, 21, MSG_KEY_P);
    printStringAt(16, 21, MSG_KEY_N);
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
  char* ordinal[6] = ORDINALS; // {"first", "second", "third", "fourth", "fifth", "sixth"};
  char upperWord[6];
  for (int k = 0; k < 5; k++) {
      upperWord[k] = word[k] - 32; // convert to uppercase
  }
  upperWord[5] = '\0';
  for (int8_t i = 1; i < 7; i++){
    char input[6];
    printStringAt((i*2)+3,13, "     ");
    {
        char attemptMsg[32];
        snprintf(attemptMsg, sizeof(attemptMsg), " %s %s %s ", MSG_PLEASE_TYPE, ordinal[i-1], MSG_GUESS);
        printStringAt(20, 32-strlen(attemptMsg), attemptMsg);
    }
    for (int8_t j = 0; j < 5; j++){
        input[j] = '';
        int colour = 1;
        int counter = 0;
        do{
          if (counter == 0)
            flashCursor((i*2)+3, j+13, colour--);
          input[j] = newGetChar(false);
          #if defined(__ZX81__) || defined(__SPECTRUM__)
            if (counter++ > 300){
              flashCursor((i*2)+3, j+13, colour);
              colour = 1 - colour;
              counter = 1;
            }
          #endif
        } while(!((input[j] >= 0x61) && (input[j] <= 0x7A) || (input[j] == 0x0c)));
        in_WaitForNoKey();
        if ((input[j] >= 0x61) && (input[j] <= 0x7A)) // alphabetic characters
          printCharAt((i*2)+3, j+13, input[j]);
        else
          if (input[j] == 0x0c && j > 0){ // rubout / delete
            printStringAt((i*2)+3, j+12, "  "); // clear deleted character and cursor
            j=j-2;
          }
          else
            j--; // repeat position
    }
    input[5] = '\0'; // null-terminate the string
    if (strcmp(input, word) == 0){
        {
          char attemptMsg[32];
          snprintf(attemptMsg, sizeof(attemptMsg), "%s%s%s %s %s %s", DARK, upperWord, LIGHT, MSG_ON, ordinal[i-1], MSG_ATTEMPT);
          #ifdef __SPECTRUM__
            clga(0, 140, 250, 50); // clear the bottom of the screen
          #else
            clga(0, 38, 64, 6); // clear the bottom of the screen
          #endif
          printStringAt(19, 8, MSG_CONGRATULATIONS);
          printStringAt(20, 5, MSG_CORRECT);
          printStringAt(21, 2, attemptMsg);
        }
        free(word);
        if (i == 6)
          return(10); // score 10 for sixth attempt
        else
          return(100 - (20 * (i-1))); //score 100 for first attempt, minus 20 for each subsequent attempt
    }else{
      for (int8_t j = 0; j < 5; j++){ // check for correct letters
        char resultMsg[6];
        if (input[j] == word[j]){
          snprintf(resultMsg, sizeof(resultMsg), "%s", MSG_RESULT_Y);
        } else if (strchr(word, input[j]) != NULL) {
          snprintf(resultMsg, sizeof(resultMsg), "%s", MSG_RESULT_P);
        } else {
          snprintf(resultMsg, sizeof(resultMsg), "%s", MSG_RESULT_N);
        }
        printStringAt((i*2)+4, j+13, resultMsg);
      }
    }
  }
  {
    char attemptMsg[36];
    snprintf(attemptMsg, sizeof(attemptMsg), "%s %s%s%s", MSG_FAIL, DARK, upperWord, LIGHT);
    printStringAt(19, 13, MSG_SORRY);
    printStringAt(20, 0, attemptMsg);
    free(word);
  }
  return(0);
}

void main(){
  unsigned long currscore = 0;
  unsigned long maxscore = 0;
    #ifdef __ZX80__
      scrolluptxt(); // help initial screen clear
    #endif
    while(true){
        menu();
        drawGameScreen();
        drawGameKey();
        displayScore(currscore, maxscore);
        currscore += queryWords(selectWord());
        maxscore += 100;
        displayScore(currscore, maxscore);
        printStringAt(23, 4, MSG_RESTART);
        newGetChar(true);
      }
}