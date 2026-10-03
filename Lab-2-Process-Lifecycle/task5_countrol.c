#include <stdio.h>
#include <unistd.h>

int main() {
    int choice = 0; // Initialized to prevent undefined behavior

    printf("current PID: %d\n", getpid());
    printf("Do you want to continue (1 for yes, 0 for no): ");
    
    // Added scanf to actually read user input
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input. Exiting...\n");
        return 1;
    }

    if (choice == 1) {
        printf("continuing...\n");
        sleep(5);
        return 0;
    } else {
        printf("Exiting..\n");
        return 1;
    }
}
