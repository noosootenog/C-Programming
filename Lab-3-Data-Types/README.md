# Lab 3: Data Types and Memory Layout

## Overview
This lab looks at how big C's basic data types are and which part of a process's memory each kind of variable lives in: the data segment, BSS, stack or heap.

## Files

| File | Description |
|------|-------------|
| `size_of_types.c` | Prints `sizeof` for `char`, `int`, `float`, `double`, `long` and a pointer. |
| `variable_addersses.c` | Prints the address of a global (data), an uninitialised global (BSS), a local (stack), a `static` local (data) and a heap allocation. |
| `pointer_heap.c` | Allocates an `int` with `malloc`, stores a value, and prints the stack address of the pointer next to the heap address it points to. |

## Build and run

```bash
gcc size_of_types.c      -o size_of_types      && ./size_of_types
gcc variable_addersses.c -o variable_addersses && ./variable_addersses
gcc pointer_heap.c       -o pointer_heap       && ./pointer_heap
```

## Where variables live

| Variable kind | Segment | Example in `variable_addersses.c` |
|---------------|---------|-----------------------------------|
| Initialised global / `static` | Data | `global_var`, `local_static` |
| Uninitialised global | BSS | `bss_var` |
| Local variable | Stack | `local_var` |
| `malloc`ed memory | Heap | `*heap_var` |

## Things to notice
* A pointer such as `heap_var` is itself a stack variable, but the memory it points to is on the heap. Its address and its value are in different regions.
* Heap addresses are lower than stack addresses on Linux.
* Addresses change between runs because of ASLR (see Lab 3.2).
