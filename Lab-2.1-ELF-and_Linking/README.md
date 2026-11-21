# Lab 2.1: C Libraries, Linking and ELF Structure

Full report: [`document/2.1.pdf`](../document/2.1.pdf)

## Overview
This lab compares **static** and **dynamic** linking using one program, then inspects the resulting ELF binaries with `readelf` and `ldd` to see how Linux loads and runs them.

## Files

| File | Description |
|------|-------------|
| `procinfo.c` | Prints the process ID, parent process ID and current time using `getpid`, `getppid`, `time` and `localtime`. |

## Build and run

```bash
gcc procinfo.c -o procinfo_dynamic            # dynamic linking (default)
gcc -static procinfo.c -o procinfo_static     # static linking
./procinfo_dynamic
./procinfo_static
ls -lh procinfo_*                             # compare file sizes
```

## Static vs dynamic linking

| Metric | Dynamic (`procinfo_dynamic`) | Static (`procinfo_static`) |
|--------|------------------------------|----------------------------|
| File size | Small (16 KB) | Large (961 KB) |
| Library dependency | Needs `libc.so.6` at runtime | None, self-contained |
| Memory use | Library code shared between processes | Library code duplicated per process |
| Security updates | Picked up automatically from the system library | Binary must be rebuilt |
| Portability | Needs a compatible glibc on the target | Runs on any compatible kernel |

## Inspecting ELF binaries

| Command | What to look at |
|---------|-----------------|
| `readelf -h <file>` | File type (`DYN` for PIE, `EXEC` for static), machine (x86-64), entry point |
| `readelf -l <file>` | `INTERP` (dynamic linker path), `LOAD` segment flags, `GNU_STACK` (should be `RW`, not executable) |
| `readelf -d <file>` | `NEEDED` entries listing the required shared libraries |
| `ldd <file>` | Resolved paths of each shared library. A static binary reports `not a dynamic executable`. |

For `procinfo_dynamic`, `ldd` shows `linux-vdso.so.1` (kernel-provided fast system call entry), `libc.so.6`, and `/lib64/ld-linux-x86-64.so.2` (the dynamic linker that loads everything before `main()` runs).

## Proof of execution
Terminal screenshots of the builds and the `readelf` / `ldd` output are stored in the [`images/`](images/) folder.
