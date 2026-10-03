#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int  main(void) {
 //GET CURRENT PROCESS IDD
	pid_t my_pid = getpid();
	pid_t my_ppid =getppid();

// Get current time
	time_t current_time =time(NULL);
	struct tm *time_info = localtime(&current_time);

//Format display information
	printf("=== Process Information === \n");
	printf ("My process ID (PID) : %d\n",my_pid);
	printf ("My parent  process ID (PPID) : %d\n",my_ppid);
	printf("Current Time:  %s\n",asctime(time_info));
	printf("Executable Path : /proc/self/exe\n");
	return 0;

}	
