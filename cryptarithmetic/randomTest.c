#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int num, i, j, **intArray;
	time_t t;
	num = 10;

	intArray = (int**) malloc(num * sizeof(int*));	
	srand((unsigned)time(&t));

	for(i=0; i<num; i++) {

		intArray[i] = (int*) malloc(num *sizeof(int));

		for(j=0; j<num; j++) {
			intArray[i][j] = rand() % 20;
			printf("%3d ", intArray[i][j]);
		}
		printf("\n");
	}

	printf("\n");

	return 0;
}
	
