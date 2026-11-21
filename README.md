# C Programming & Operating Systems

Lab work for **ST5039CMD – Programming and Operating Systems** (Batch 39C), BSc (Hons) Ethical Hacking and Cybersecurity, Softwarica College of IT & E-commerce in collaboration with Coventry University.

Each lab explores how C programs interact with the operating system, from compilation and linking, through process management, to how memory is laid out at runtime. Every lab folder contains the source code and a README with build instructions and key observations. Terminal screenshots are kept in each lab's `images/` folder as proof of execution, and the full written reports are collected as PDFs in [`document/`](document/).

## Labs

| Lab | Topic | Folder | Report |
|-----|-------|--------|--------|
| 1 | The C compilation pipeline: preprocess, compile, assemble, link | [`Lab-1-Compilation`](Lab-1-Compilation/) | [1.pdf](document/1.pdf) |
| 2 | Process lifecycle: PID/PPID, exit codes, standard I/O, termination | [`Lab-2-Process-Lifecycle`](Lab-2-Process-Lifecycle/) | [2.pdf](document/2.pdf) |
| 2.1 | C libraries, static vs dynamic linking, ELF structure | [`Lab-2.1-ELF-and_Linking`](Lab-2.1-ELF-and_Linking/) | [2.1.pdf](document/2.1.pdf) |
| 3 | Data type sizes and where variables live in memory | [`Lab-3-Data-Types`](Lab-3-Data-Types/) | n/a |
| 3.1 | Data, read-only data and text segments | [`Lab-3.1-Data-Segment`](Lab-3.1-Data-Segment/) | n/a |
| 3.2 | Mapping `.bss`, heap and stack with GDB and `readelf` | [`Lab-3.2-Mapping-Address-and-GNU-Debugging`](Lab-3.2-Mapping-Address-and-GNU-Debugging/) | [3.2.pdf](document/3.2.pdf) (lab sheet) |

## Repository structure

├── document/
│   ├── 1.pdf
│   ├── 2.1.pdf
│   ├── 2.pdf
│   └── 3.2.pdf
├── Lab-1-Compilation/
│   ├── images/
│   │   ├── image1.png
│   │   ├── image2.png
│   │   ├── image3.png
│   │   ├── image4.png
│   │   ├── image5.png
│   │   ├── image6.png
│   │   ├── image7.png
│   │   └── image8.png
│   ├── hello
│   ├── hello.c
│   ├── hello.i
│   ├── hello.o
│   ├── hello.s
│   └── README.md
├── Lab-2-Process-Lifecycle/
│   ├── images/
│   │   ├── image1.png
│   │   ├── image10.png
│   │   ├── image11.png
│   │   ├── image12.png
│   │   ├── image13.png
│   │   ├── image2.png
│   │   ├── image3.png
│   │   ├── image4.png
│   │   ├── image5.png
│   │   ├── image6.png
│   │   ├── image7.png
│   │   ├── image8.png
│   │   └── image9.png
│   ├── README.md
│   ├── task1_alive.c
│   ├── task2_identity.c
│   ├── task3_exit.c
│   ├── task4_input.c
│   └── task5_countrol.c
├── Lab-2.1-ELF-and_Linking/
│   ├── images/
│   │   ├── image1.png
│   │   ├── image10.png
│   │   ├── image11.png
│   │   ├── image2.png
│   │   ├── image3.png
│   │   ├── image4.png
│   │   ├── image5.png
│   │   ├── image6.png
│   │   ├── image7.png
│   │   ├── image8.png
│   │   └── image9.png
│   ├── procinfo.c
│   └── README.md
├── Lab-3-Data-Types/
│   ├── pointer_heap.c
│   ├── README.md
│   ├── size_of_types.c
│   └── variable_addersses.c
├── Lab-3.1-Data-Segment/
│   ├── demo2.c
│   └── README.md
├── Lab-3.2-Mapping-Address-and-GNU-Debugging/
│   ├── demo.c
│   ├── gbd_session_trimmed.log
│   ├── gdb_commands
│   └── README.md
├── .gitignore
├── LICENSE
└── README.md


## Requirements

All labs were written and tested on Ubuntu/Linux (x86-64).

| Tool | Used for | Install |
|------|----------|---------|
| `gcc` | Compiling C programs | `sudo apt install build-essential` |
| `gdb` | Debugging and memory inspection (Lab 3.2) | `sudo apt install gdb` |
| `readelf`, `ldd` | Inspecting ELF binaries (Labs 1, 2.1, 3.2) | Included with `binutils` / `libc-bin` |

## Getting started

```bash
git clone https://github.com/noosootenog/C-Programming.git
cd C-Programming/Lab-1-Compilation
gcc hello.c -o hello && ./hello
```

Each lab README lists the exact commands for that lab.

## License

Released under the [MIT License](LICENSE).
