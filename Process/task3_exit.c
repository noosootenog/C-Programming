#include <stdio.h>

int main () {
	int num;
	printf("Enter ana number(positive for success and negative for fail): ");
	scanf("%d",&num);
	
	if (num > 0) {
		printf("Success\n");
		return 0; // Tell OS Success
	} else {
		printf("Failure\n");
		return 1; //  Tell OS  FAilure		
	}
}


