# zxordle

**zxordle** is a word puzzle game designed to run on the Sinclair ZX80, Sinclair ZX81, Timex Sinclar 1000 and Timex Sinclair 1500 with 16KB of RAM. It's based on a game originally by Josh Wardle.

Players have six attempts to guess a hidden five-letter word. After each guess, the game provides feedback to help narrow down the possibilities.

## Getting Started

### ZX80

Load the zxordle.O file on your ZX80 or compatible emulator and start guessing words!

### ZX81

Load the zxordle.P file on your ZX81, TS1000, TS1500 or compatible emulator and start guessing words!

## Compiling

zxordle is written in C using the Z88DK development kit for Z80 systems.

Once the Z88DK development kit is installed on a modern system, zxordle can compiled by running the following command:
```
make
```

This has been tested with Z88DK v2.3 and the ZEsarUX v12 emulator.