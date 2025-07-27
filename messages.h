// messages.h
#ifndef MESSAGES_H
#define MESSAGES_H

#define MSG_NAME "WORZXLE"

#define ORDINALS {"first", "second", "third", "fourth", "fifth", "sixth"}

#if defined(__ZX81__) || defined(__ZX80__)
    #define DARK ""
    #define LIGHT ""
    #define MSG_SCORE "score"
    #define MSG_CURSOR "\x5f"
    #define MSG_EMPTY_SQUARE " "
    #define MSG_BLACK_SQUARE "@"
    #define MSG_BLACK_LINE "@@@@@@@@@"
    #define MSG_VERSION "version"

    #define MSG_AUTHOR "by stephen bowyer"
    #define MSG_BASED_ON "based on a game by josh wardle"
    #define MSG_DESC1 "a word puzzle where six"
    #define MSG_DESC2 "attempts are offered to guess"
    #define MSG_DESC3 "the hidden five-letter word"
    #define MSG_START "press any key to start"
    #define MSG_RESTART "press any key to restart"

    #define MSG_RESULT_Y "Y"
    #define MSG_RESULT_P "P"
    #define MSG_RESULT_N "N"

    #define MSG_KEY_Y "Y correct"
    #define MSG_KEY_P "P misplaced"
    #define MSG_KEY_N "N incorrect"

    #define MSG_PLEASE_TYPE "please type your"
    #define MSG_GUESS "guess"

    #define MSG_CONGRATULATIONS "congratulations"
    #define MSG_CORRECT "you correctly guessed"
    #define MSG_ON "on your"
    #define MSG_ATTEMPT "attempt"

    #define MSG_FAIL "you did not find the word"
    #define MSG_SORRY "sorry"
#elif defined(__SPECTRUM__)
    #define DARK "\x14\x31"
    #define LIGHT "\x14\x30"
    #define MSG_SCORE "Score"
    #define MSG_CURSOR MSG_BLACK_SQUARE
    #define MSG_EMPTY_SQUARE " "
    #define MSG_BLACK_SQUARE "\x14\x31 \x14\x30"
    #define MSG_BLACK_LINE "\x14\x31         \x14\x30"
    #define MSG_VERSION "Version"

    #define MSG_AUTHOR "By Stephen Bowyer"
    #define MSG_BASED_ON "Based on a game by Josh wardle"
    #define MSG_DESC1 "A word puzzle where six"
    #define MSG_DESC2 "attempts are offered to guess"
    #define MSG_DESC3 "the hidden five-letter word"
    #define MSG_START "Press any key to start"
    #define MSG_RESTART "Press any key to restart"

    #define MSG_TRAD_PRESS "Press T for traditional mode"
    #define MSG_TRAD_ON "Traditional mode ON"
    #define MSG_TRAD_OFF "Traditional mode OFF"

    #define MSG_COLOUR_Y_ON "\x11\x04"
    #define MSG_COLOUR_Y_OFF "\x11\x07"
    #define MSG_COLOUR_P_ON "\x11\x06"
    #define MSG_COLOUR_P_OFF "\x11\x07"
    #define MSG_COLOUR_N_ON "\x11\x02"
    #define MSG_COLOUR_N_OFF "\x11\x07"

    #define MSG_RESULT_Y "\x11\x04Y\x11\x07"
    #define MSG_RESULT_P "\x11\x06P\x11\x07"
    #define MSG_RESULT_N "\x11\x02N\x11\x07"

    #define MSG_KEY_Y "\x11\x04Y\x11\x07 Correct"
    #define MSG_KEY_P "\x11\x06P\x11\x07 Misplaced"
    #define MSG_KEY_N "\x11\x02N\x11\x07 Incorrect"

    #define MSG_PLEASE_TYPE "Please type your"
    #define MSG_GUESS "guess"

    #define MSG_CONGRATULATIONS "Congratulations"
    #define MSG_CORRECT "You correctly guessed"
    #define MSG_ON "on your"
    #define MSG_ATTEMPT "attempt"

    #define MSG_FAIL "You did not find the word"
    #define MSG_SORRY "Sorry"
#endif


#endif // MESSAGES_H