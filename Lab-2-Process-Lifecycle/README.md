# Lab 2: Process Lifecycle

## Overview
This lab covers how Linux processes are created, identified, controlled, and terminated from C.

## Files

| File | Description |
|------|-------------|
| `task1_alive.c` | Prints a start message, sleeps 30 seconds, then prints a finish message. |
| `task2_identity.c` | Prints the process ID (`getpid`) and parent process ID (`getppid`), then sleeps 20 seconds. |
| `task3_exit.c` | Reads a number; returns exit status 0 (success) for positive, 1 (failure) for negative. |
| `task4_input.c` | Reads the user's name and prints a welcome message. |
| `task5_countrol.c` | Prints the current PID and asks the user whether to continue or exit. |

## How to Compile & Run

```bash
gcc task1_alive.c -o task1_alive && ./task1_alive
gcc task2_identity.c -o task2_identity && ./task2_identity
gcc task3_exit.c -o task3_exit && ./task3_exit
gcc task4_input.c -o task4_input && ./task4_input
gcc task5_countrol.c -o task5_countrol && ./task5_countrol
```

Check the exit status of a program with:

```bash
echo $?
```

## Documentation & Screenshots

![Figure 1: task1_alive](images/image10.png)
![Figure 2: Terminal 1](images/image12.png)
![Figure 3: Terminal 2](images/image4.png)
![Figure 4: task1_alive](images/image2.png)
![Figure 5: Terminal 1](images/image13.png)
![Figure 6: Terminal 2](images/image9.png)
![Figure 7: task3_exit](images/image8.png)
![Figure 8: Testing task3_exit](images/image6.png)
![Figure 9: task4_input.c](images/image3.png)
![Figure 10: Executing Task4_input](images/image11.png)
![Figure 11: task5_countrol](images/image7.png)
![Figure 12: Executing task5_countrol](images/image5.png)
