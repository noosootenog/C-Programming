#include <stdio.h>
#include <unistd.h>

int main () {
	//Get process id
	pid_t my_pid =getpid();

	// Get pranet process id 
	pid_t my_ppid =getppid();

	printf("My PID is : %d\n", my_pid);
	printf("My Parent PID is :  %d\n", my_ppid);

	printf("sleeping for 20 seconds .... \n");
	sleep(20);
	
	return 0;
}

