# Lab 1: C Compilation Flow

**Author:** Subigya Raut
**Course:** ST5039CMD Programming and Operating Systems
**Date:** 29 September, 2026

## Objective
Understand the four stages GCC goes through to turn a C source file into a running executable: preprocess, compile, assemble, and link.

## Files

| File | Stage | Description |
|------|-------|-------------|
| `hello.c` | Source | Prints `This is Batch 39C:` |
| `hello.i` | Preprocessed | Source with `#include <stdio.h>` expanded |
| `hello.s` | Assembly | x86-64 assembly generated from `hello.i` |
| `hello.o` | Object | Relocatable ELF object, not yet linked |
| `hello` | Executable | Final dynamically linked ELF binary |

## 1. Installing GCC

Install the `build-essential` package, which provides `gcc` and related tools.

```bash
sudo apt install build-essential
```

![Installing build-essential](./images/install-build-essential.png)
*Figure 1: Install build-essential*

## 2. Working Mechanism of C

### Creating `hello.c`

Create and edit the file with `nano`:

```bash
nano hello.c
```

![Writing hello.c in nano](./images/nano-writing-hello-c.png)
*Figure 2: Writing hello.c*

![Contents of hello.c](./images/hello-c-source.png)
*Figure 3: hello.c*

### i) Preprocess

Expands `#include` and `#define` directives and strips comments.

```bash
gcc -E hello.c -o hello.i
```

![Preprocessed output hello.i](./images/preprocess-hello-i.png)
*Figure 4: hello.i*

The 79-byte `hello.c` grows to over 21 KB because the contents of `stdio.h` are pasted in.

### ii) Compile

Translates the preprocessed C code into assembly.

```bash
gcc -S hello.i -o hello.s
```

![Assembly output hello.s](./images/compile-hello-s.png)
*Figure 5: hello.s*

### iii) Assemble

Converts the assembly into machine code in a relocatable object file.

```bash
gcc -c hello.s -o hello.o
```

![Object file hello.o](./images/assemble-hello-o.png)
*Figure 6: hello.o*

### iv) Link

Links the object file with libc to produce the final executable.

```bash
gcc hello.o -o hello
./hello
```

![Linked executable hello](./images/link-hello.png)
*Figure 7: hello*

Expected output:

```
This is Batch 39C:
```

## Key Takeaways
- Compilation is a pipeline of four separate stages, each producing an inspectable file.
- Preprocessing handles `#include` and `#define` before any compilation happens.
- `hello.o` can't run on its own; the linker resolves `printf` from libc to make `hello` executable.
