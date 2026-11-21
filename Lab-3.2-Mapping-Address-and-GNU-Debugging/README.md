# Lab 3.2: Mapping the Address Space with GDB

Lab sheet: [`document/3.2.pdf`](../document/3.2.pdf)

## Overview
This lab uses GDB, `readelf` and the kernel's memory map to find where `.bss`, the heap and the stack sit in a running process, and to read the raw values stored there.

## Files

| File | Description |
|------|-------------|
| `demo.c` | One uninitialised global (BSS), one local (stack) and one `malloc`ed `int` (heap). |
| `gdb_commands.gdb` | The GDB commands used in this lab; run with `gdb -batch -x gdb_commands.gdb ./demo`. |
| `gdb_session_trimmed.log` | Captured session output (shared-library rows trimmed from `info files`). |

Tested on Ubuntu 24.04 x86-64, gcc 13.3, GDB 15.1. Your addresses will differ, but the relationships between them stay the same.

## Procedure

```bash
gcc -g demo.c -o demo
gdb ./demo
(gdb) break 23                 # lands on line 24, the next executable line
(gdb) run
(gdb) info files               # section addresses, including .bss
(gdb) print &bss_global_var
(gdb) info proc mappings       # kernel's view: [heap] and [stack]
(gdb) print stack_local_var
(gdb) print &stack_local_var
(gdb) x/4wx $sp                # raw words at the top of the stack
(gdb) print heap_ptr
(gdb) x/1wd heap_ptr           # the heap value
(gdb) continue
(gdb) quit
readelf -l demo                # program headers, compared with GDB
```

## Results

| Region | Start | End | Variable inside |
|--------|-------|-----|-----------------|
| `.bss` | `0x555555558010` | `0x555555558018` | `&bss_global_var` = `0x555555558014` |
| `[heap]` | `0x555555559000` | `0x55555557a000` | `heap_ptr` = `0x5555555592a0` |
| `[stack]` | `0x7ffffffde000` | `0x7ffffffff000` | `&stack_local_var` = `0x7fffffffe81c` |

* **`readelf` vs GDB:** `readelf` shows `.bss` at offset `0x4010`. The binary is a PIE, so the loader adds the base `0x555555554000`, giving the `0x555555558010` that GDB reports.
* **BSS has no file size:** the RW `LOAD` segment has `MemSiz` 0x280 and `FileSiz` 0x278. The 8-byte difference is `.bss`, zero-filled by the kernel at load time.
* **`x/4wx $sp`:** the fourth word is `0x0000002a` (42), located at `$sp + 12` = `&stack_local_var`.

## The `x/1wd` command
`x/NFU address` examines memory: `1` is the count (one unit), `w` is the unit size (a 4-byte word), and `d` is the output format (signed decimal). `x/1wd heap_ptr` therefore reads 4 bytes at the address in `heap_ptr` and prints `99`.

## Post-lab questions

**1. Do the stack and heap move toward each other?**
The heap sits at low addresses and grows up; the stack sits at high addresses and grows down. The gap is `0x7ffffffde000 - 0x55555557a000 = 0x2AAAAAA64000` (about 42.7 TiB). Growing the heap by *n* bytes or the stack by *m* bytes reduces it to `0x2AAAAAA64000 - n - m`, so the two regions approach each other.

**2. Same addresses in two terminals?**
Outside GDB, no. Linux randomises the executable, heap, stack and library bases on every run (ASLR); two runs here printed `0x55994c2ae014` and `0x561e240eb014` for the BSS variable. Even if two processes did get the same virtual address, each has its own page table, so the address maps to different physical memory. This is process isolation. GDB disables ASLR by default, which is why the addresses above are repeatable.
