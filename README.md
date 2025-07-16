# zxordle

**zxordle** is a word puzzle game designed to run on the Sinclair ZX80, Sinclair ZX81, Sinclair ZX Spectrum and compatible Timex Sinclair computers with at least 16KB of RAM. It's based on a game originally by Josh Wardle.

Players have six attempts to guess a hidden five-letter word. After each guess, the game provides feedback to help narrow down the possibilities.

## Getting Started

### ZX80

A 16KB or larger RAM pack is required.

Load the zxordle.O file on your ZX80 or compatible emulator and start guessing words!

### ZX81

A 16KB or larger RAM pack is required.

Load the zxordle.P file on your ZX81, TS1000, TS1500 or compatible emulator and start guessing words!

### ZX Spectrum

Works on all models of ZX Spectrum, from 16KB to +3.

Load the zxordle.tap file on your ZX Spectrum or compatible emulator and start guessing words!

## Compiling

zxordle is written in C using the Z88DK development kit for Z80 systems.

Once the Z88DK development kit is installed on a modern system, zxordle can compiled by running the following command:
```
make
```

This has been tested with Z88DK v2.3 and the ZEsarUX v12 emulator.