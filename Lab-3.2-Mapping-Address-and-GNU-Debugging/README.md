# Lab 3.2 – Mapping Address Space with GNU Debugger (GDB)

**Topic:** Process runtime topography – locating `.bss`, `[heap]` and `[stack]` using GDB, `readelf` and the kernel's memory map.

## Learning objectives
1. Evaluate the address boundaries separating static allocations (`.bss`) from dynamic regions (heap, stack).
2. Navigate runtime program contexts using GDB subcommands.

## Files
| File | Purpose |
|---|---|
| `demo.c` | Target program (one global, one local, one `malloc`) |
| `gdb_commands.gdb` | The GDB commands of Tasks B–E, runnable with `gdb -batch -x` |
| `gdb_session_trimmed.log` | Captured session output (shared-library rows trimmed from `info files`) |

> Environment used: Ubuntu 24.04, x86-64, gcc 13.3.0, GDB 15.1. Addresses will differ on your machine; the relationships between them will not.

---

## Source code (`demo.c`)
```c
#include <stdio.h>
#include <stdlib.h>

// 1. BSS Section (Uninitialized global data, defaults to 0)
int bss_global_var;

int main() {
    // 2. Stack Section (Local variables)
    int stack_local_var = 42;

    // 3. Heap Section (Dynamically allocated memory)
    int *heap_ptr = (int *)malloc(sizeof(int));
    if (heap_ptr == NULL) {
        return 1;
    }
    *heap_ptr = 99; // Assign value to heap memory

    printf("Addresses:\n");
    printf("BSS (Global): %p\n", (void*)&bss_global_var);
    printf("Stack (Local): %p\n", (void*)&stack_local_var);
    printf("Heap (Dynamic): %p\n", (void*)heap_ptr);

    // Breakpoint here to inspect memory
    printf("Ready for GDB inspection!\n");

    free(heap_ptr);
    return 0;
}
```

---

## Task A – Build with debugging symbols
```bash
gcc -g demo.c -o demo
```
`-g` embeds DWARF debug info (variable names, types, line numbers) so GDB can map machine code back to the source.

## Task B – Breakpoint and run
```bash
gdb ./demo
(gdb) break 23
(gdb) run
```
Line 23 is only a comment, so GDB moves the breakpoint to the next executable line:
```
Breakpoint 1 at 0x1277: file demo.c, line 24.
Breakpoint 1, main () at demo.c:24
24	    printf("Ready for GDB inspection!\n");
```
At this point `stack_local_var` and `heap_ptr` are both live.

## Task C – Locate the `.bss` segment
```
(gdb) info files
    ...
    0x0000555555558000 - 0x0000555555558010 is .data
    0x0000555555558010 - 0x0000555555558018 is .bss

(gdb) print &bss_global_var
$1 = (int *) 0x555555558014 <bss_global_var>
```
`0x555555558010 ≤ 0x555555558014 < 0x555555558018`, so the global variable lies **inside** `.bss`. `.bss` is only 8 bytes: the 4-byte `bss_global_var` plus alignment/padding (`completed.0`, the small libc housekeeping flag).

## Task D – `readelf` (program header on disk)
```bash
readelf -l demo      # program headers
readelf -S -W demo   # section headers
```
Relevant output:
```
LOAD  0x2d98  0x3d98  0x3d98   FileSiz 0x278  MemSiz 0x280   RW   0x1000
05    .init_array .fini_array .dynamic .got .data .bss

[26] .bss  NOBITS  0000000000004010  003010  000008
```

**Comparison with GDB**
* `readelf` shows *link-time offsets*; GDB shows *runtime addresses*. The binary is a PIE (`Type: DYN`), so the loader adds a base of `0x555555554000`:
  `0x555555554000 + 0x4010 = 0x555555558010` ✔ (start of `.bss` in GDB).
* The RW `LOAD` segment has `MemSiz − FileSiz = 0x280 − 0x278 = 0x8` bytes. Those 8 bytes exist only in memory and are zero-filled by the kernel. That is the definition of `.bss` (`NOBITS`: it occupies no space in the file).

## Task E – Kernel address tables
```
(gdb) info proc mappings
          Start Addr           End Addr       Size     Offset  Perms  objfile
      0x555555554000     0x555555555000     0x1000        0x0  r--p   /home/claude/lab/demo
      0x555555555000     0x555555556000     0x1000     0x1000  r-xp   /home/claude/lab/demo   (.text)
      0x555555556000     0x555555557000     0x1000     0x2000  r--p   /home/claude/lab/demo   (.rodata)
      0x555555557000     0x555555558000     0x1000     0x2000  r--p   /home/claude/lab/demo   (RELRO)
      0x555555558000     0x555555559000     0x1000     0x3000  rw-p   /home/claude/lab/demo   (.data/.bss)
      0x555555559000     0x55555557a000    0x21000        0x0  rw-p   [heap]
      ... libc, ld.so, [vvar], [vdso] ...
      0x7ffffffde000     0x7ffffffff000    0x21000        0x0  rw-p   [stack]
  0xffffffffff600000 0xffffffffff601000     0x1000        0x0  --xp   [vsyscall]
```

## Task F – Registers and raw memory
```
(gdb) print stack_local_var
$2 = 42
(gdb) print &stack_local_var
$3 = (int *) 0x7fffffffe81c
(gdb) x/4wx $sp
0x7fffffffe810: 0x00000000  0x00000000  0xf7fe5ae0  0x0000002a

(gdb) print heap_ptr
$4 = (int *) 0x5555555592a0
(gdb) x/1wd heap_ptr
0x5555555592a0: 99
```
* `0x0000002a` (= 42) is the fourth word, at `0x7fffffffe810 + 12 = 0x7fffffffe81c`, exactly `&stack_local_var`. The variable sits 12 bytes above `$sp`.
* The heap value 99 sits at `0x5555555592a0`, `0x2a0` bytes into the heap, after glibc's internal bookkeeping (tcache structure) at the start of the heap.

Finish:
```
(gdb) continue
(gdb) quit
```
Program output: `BSS (Global): 0x555555558014`, `Stack (Local): 0x7fffffffe81c`, `Heap (Dynamic): 0x5555555592a0` ← identical to what GDB reported.

---

# Deliverables

## 1. Logs
See `gdb_session_trimmed.log` and the transcripts above. Compilation succeeded with no warnings.

## 2. Address matrix

| Region | Start address | End address | Size | Variable address (inside region) |
|---|---|---|---|---|
| `.bss` | `0x555555558010` | `0x555555558018` | 8 B | `&bss_global_var` = `0x555555558014` |
| `[heap]` | `0x555555559000` | `0x55555557a000` | 0x21000 (132 KiB) | `heap_ptr` = `0x5555555592a0` |
| `[stack]` | `0x7ffffffde000` | `0x7ffffffff000` | 0x21000 (132 KiB) | `&stack_local_var` = `0x7fffffffe81c` |

## 3. The command `x/1wd heap_ptr`
`x` = *examine memory*. The syntax is `x/NFU address`:

| Part | Name | Meaning here |
|---|---|---|
| `1` | **N** – count | Show **one** unit. |
| `w` | **U** – unit size | A **word** = 4 bytes (`b`=1, `h`=2, `w`=4, `g`=8). Matches `sizeof(int)`. |
| `d` | **F** – format | Print as a signed **decimal** integer (`x`=hex, `u`=unsigned, `c`=char, `s`=string, `i`=instruction). |

`heap_ptr` is the address expression. GDB evaluates it to `0x5555555592a0`, reads 4 bytes from that address, and prints them as a decimal, giving `99`. Using `x/1wx` would show `0x00000063` for the same bytes.

---

# Post-lab assessment

## Q1. Stack and heap move toward each other
The heap starts at a **low** address and grows **upward** (`brk` raises its end). The stack starts at a **high** address and grows **downward**. Using the measured values:

```
Gap = stack_start − heap_end
    = 0x7ffffffde000 − 0x55555557a000
    = 0x2AAAAAA64000  ≈ 46.9 × 10^12 bytes ≈ 42.7 TiB
```
* Allocating *n* more bytes moves `heap_end` to `heap_end + n` → gap becomes `0x2AAAAAA64000 − n`.
* Each new stack frame of size *m* moves the stack low-water mark to `stack_start − m` → gap becomes `0x2AAAAAA64000 − m`.

So the gap `G(n, m) = 0x2AAAAAA64000 − n − m` strictly decreases as either region expands; i.e. they migrate toward each other. (In practice the stack is capped by `ulimit -s`, typically 8 MiB, and large `malloc`s use `mmap` rather than `brk`, so they never actually collide on 64-bit systems.)

Supporting evidence from this run: `heap_ptr` (`0x5555…`) < `&stack_local_var` (`0x7fff…`), and local variables sit at ever lower addresses as frames are pushed.

## Q2. Two terminals running the program at once
**Not the same addresses (outside GDB) — but they would not collide even if they were.**

Observed outside GDB (two runs of `./demo`):
```
Run 1: BSS 0x55994c2ae014   Stack 0x7ffd6243a25c   Heap 0x559973aad2a0
Run 2: BSS 0x561e240eb014   Stack 0x7ffed3d6901c   Heap 0x561e617802a0
```
* **Virtual memory:** every process gets its own page table, so each has a private virtual address space. An address like `0x…8014` is meaningful only inside the process that uses it; the MMU maps it to different physical frames for each process. Two processes may even use the *same* virtual address with no conflict, because they translate to different physical RAM. This is process isolation.
* **ASLR:** Linux additionally randomises the base of the executable (PIE), heap, stack and libraries at each launch, so the addresses differ between runs, as seen above. Only the low 12 bits (page offset: `…014`, `…2a0`) stay stable, because randomisation works in page units.
* **Why GDB showed `0x5555…`:** GDB disables ASLR by default (`set disable-randomization on`), which is why the lab addresses are reproducible. Under GDB, two runs would print identical addresses; still without conflict, for the reasons above.
