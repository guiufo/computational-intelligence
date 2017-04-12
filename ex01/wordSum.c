// Simple program to solve "send + more = money"
// Author: Guilherme Martini
// Date: 4 April 2017

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define SIZE 8

int *generateIndividual(void);

int main() {
	char word1[] = "send";
	char word2[] = "more";
	char result[] = "money";
	// Each individual has 8 positions
	int sendmory[SIZE] = {0,1,2,3,4,5,6,7};

	int *individual01;
	individual01 = generateIndividual(); 

	for(int i = 0; i < SIZE; i++)
		printf("%d ", individual01[i]);
	printf("\n");

	return 0;
}

int shuffle(int individual) {
	return 0;
}

int *generateIndividual(void) {
	// numbers go from 0 to 9 without repetition
	int i;
	int n = 10;	
	bool arr[SIZE]={0};
	int *individual;
	time_t t;

	individual = (int*)(malloc(sizeof(int) * SIZE)); 
	srand((unsigned)time(&t)); 

	for(i=0;i<n;++i)
	{
		int r=rand()%9;
		if(!arr[r]) 
			individual(i*sizeof(int)) = r;
		else i--;
		arr[r]=1;
	}

	return individual; 
}
	

int generateIndividuals(int numberOfIndividuals) {
	int i,j; 

	for(i=0; i<numberOfIndividuals; i++) {
		for(j=0; j<SIZE; j++) {
			srand(time(NULL));
			//individuals[i][j] = rand();
		}
	}
}

int evaluate(int individual) {
} 
