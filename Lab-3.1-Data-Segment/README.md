# Lab 3.1: Data, Read-Only Data and Text Segments

## Overview
This lab extends Lab 3 to the segments that are stored in the executable file itself: initialised data, read-only data and program code.

## Files

| File | Description |
|------|-------------|
| `demo2.c` | Defines an initialised global, a string literal and a function, and prints the address of each. |

## What the program places where

| Item in `demo2.c` | Segment |
|-------------------|---------|
| `int data_global_var = 0x12345678;` | `.data`: initialised global data |
| The string `" Text_Segment_Verification"` | `.rodata`: read-only constants |
| `check_execution()` | `.text`: executable code |

The pointer `text_string_literal` is itself a global in `.data`. Its *value*, which is what the program prints, is an address in `.rodata`.

## Build and run

```bash
gcc -g demo2.c -o demo2
./demo2
readelf -S demo2     # compare the printed addresses with the .data, .rodata and .text sections
```

The program ends with a comment marking where to place a GDB breakpoint, so it can also be examined with `gdb ./demo2` as in Lab 3.2.
