#include <stdio.h>
#include <unistd.h>

int main() {
	printf("I am Starting \n");

	//Loop for 30 seconsds
	for(int i=1; i<= 30 ; i++) {
		sleep(1); // Pause execution for 1 second
	}

	printf("Finished. \n");
	return 0;
}


