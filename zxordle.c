#include <stdio.h>
#include <stdbool.h>
#include <input.h>
#include <time.h>
#include <zx81.h>
#include <math.h>
#include <string.h>
#include "wordlist.h"

#define VER "0.1"
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

void animateLogo(){
    int8_t ranPos = rand() % 7; // which character to animate
    int8_t ranColour = rand() % 2; // which colour to use
    char* myName = NAME;
    char* myChar = myName[ranPos];
    if (ranColour == 1)
        myChar += 32; // convert to lowercase for black on white
    printCharAt(5, 12+ranPos, myChar);
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
            clga(2, 16, 60, 18);
            break;
        }
        animateLogo();
    }
}

void main(){
    while(true){
        menu();
    }
}