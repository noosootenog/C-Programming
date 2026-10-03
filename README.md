# C-Programming

Hands-on lab work for learning C and understanding how programs actually run on Linux: from source code to executable, through the process lifecycle, ELF linking, and memory layout.

## Labs

| Lab | Topic | What it covers |
|-----|-------|----------------|
| [Lab 1](./Lab-1-Compilation) | Compilation | The four GCC stages: preprocess, compile, assemble, link |
| [Lab 2](./Lab-2-Process-Lifecycle) | Process Lifecycle | PIDs, parent PIDs, exit codes, user input, and process control |
| [Lab 2.1](./Lab-2.1-ELF-and_Linking) | ELF and Linking | libc, static vs. dynamic linking, and ELF structure |
| [Lab 3](./Lab-3-Data-Types) | Data Types and Memory | Type sizes, and stack, heap, and data segment addresses |

## Requirements

- Linux (or WSL on Windows)
- `gcc` and `binutils` (`readelf`, `objdump`, `nm`, `ldd`)

```bash
sudo apt install build-essential
```

## Getting Started

```bash
git clone https://github.com/noosootenog/C-Programming.git
cd C-Programming
```

Each lab folder has its own README with build and run instructions.

## Repository Structure

```
C-Programming/
├── Lab-1-Compilation/          # hello.c and its .i, .s, .o intermediates
├── Lab-2-Process-Lifecycle/    # task1 to task5
├── Lab-2.1-ELF-and_Linking/    # procinfo.c, static and dynamic builds
├── Lab-3-Data-Types/           # sizeof, addresses, heap pointer
├── LICENSE
└── README.md
```

## License

Released under the [MIT License](./LICENSE).
