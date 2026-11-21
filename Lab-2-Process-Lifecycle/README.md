# Lab 2: Process Lifecycle

Full report: [`document/2.pdf`](../document/2.pdf)

## Overview
This lab looks at how a process is created, identified, observed and terminated on Linux. Five small programs demonstrate long-running processes, process identity, exit status, standard input and conditional termination.

## Files

| File | Task | Description |
|------|------|-------------|
| `task1_alive.c` | 1. Long-running process | Prints a start message, loops with `sleep(1)` for 30 seconds, then prints a finish message. |
| `task2_identity.c` | 2. Process identity | Prints its PID (`getpid`) and parent PID (`getppid`), then sleeps for 20 seconds. |
| `task3_exit.c` | 3. Exit codes | Reads a number. Returns `0` (success) if positive, `1` (failure) otherwise. |
| `task4_input.c` | 4. Standard I/O | Reads a name from `stdin` and prints a welcome message. |
| `task5_countrol.c` | 5. Conditional termination | Prints its PID, asks whether to continue, and exits with `0` or `1` depending on the answer. |

## Build and run

```bash
gcc task1_alive.c    -o task1_alive    && ./task1_alive
gcc task2_identity.c -o task2_identity && ./task2_identity
gcc task3_exit.c     -o task3_exit     && ./task3_exit
gcc task4_input.c    -o task4_input    && ./task4_input
gcc task5_countrol.c -o task5_countrol && ./task5_countrol
```

## Observing the processes
Tasks 1 and 2 are run in the background with `&` so a second terminal can inspect them:

```bash
./task1_alive &                      # terminal 1
ps aux | grep task1_alive            # terminal 2
ps -p <PID> -o pid,ppid,cmd          # terminal 2: confirm PID and parent PID
```

Tasks 3 and 5 report success or failure through their exit status. Read it right after the program ends:

```bash
echo $?    # 0 = success, non-zero = failure
```

## Key observations
* A background process keeps running and appears in `ps` with its own PID.
* The PID printed by the program matches what `ps` reports, and the PPID is the shell that started it.
* The shell reads a program's exit status from `$?`, which is how scripts detect success or failure.

## Proof of execution
Terminal screenshots for all five tasks are stored in the [`images/`](images/) folder.
