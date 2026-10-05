# Lab 3: Data Types

## Overview
This lab explores C data types, their sizes, and where variables live in memory (stack, heap, data/BSS segments).

## Files

| File | Description |
|------|-------------|
| `size_of_types.c` | Prints the size in bytes of `char`, `int`, `float`, `double`, `long`, and a pointer. |
| `variable_addersses.c` | Prints the memory addresses of variables stored in different segments: global (data), uninitialized (BSS), local (stack), static, and heap. |
| `pointer_heap.c` | Allocates memory on the heap with `malloc`, stores a value, and prints the stack address of the pointer vs the heap address of the data. |

## How to Compile & Run

```bash
gcc size_of_types.c -o size_of_types && ./size_of_types
gcc variable_addersses.c -o variable_addersses && ./variable_addersses
gcc pointer_heap.c -o pointer_heap && ./pointer_heap
```
