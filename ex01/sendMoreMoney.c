// Send More Money Problem
// Genetic Algorithms Approach
// Author: Guilherme Martini
// Date: 14 April 2017

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

#define ISIZE	10		// Individual size
#define PSIZE 	100		// Initial population size
#define PMUT	0.1		// Mutation rate
#define PCROSS	0.8		// Crossover rate
#define NGEN	200		// Number of generations

int **generateIndividuals(int **population);
int **evaluatePopulation(int **population);
int **tournament(int **population, int tour);
int **cyclicCrossover(int **population);
int **evaluateChildren(int **population);

void maxMinEval(int **population);
void mean(int **population);
void printPopulation(int **population);


int main(int argc, char *argv[]) {
	int **population, i, j;
	int nrows, ncolumns;

	// Total size of population plus space for children
	nrows = PSIZE + PSIZE*PCROSS;
	// 8 for individual, 2 for permutation, 1 for fitness score
	ncolumns = ISIZE + 1;

	// Allocate matrix for population
	// Each row from index 0 to 7 corresponds to "sendmory"
	population = (int**) malloc(nrows * sizeof(int*));
	for(i=0; i < nrows; i++)
		population[i] = (int*) malloc(ncolumns * sizeof(int));

	// Generate random population
	population = generateIndividuals(population);
	// Evaluate each individual
	population = evaluatePopulation(population);
	// Print max and min evaluation values
	maxMinEval(population);	
	// Calculate and print the mean of evals
	mean(population);
	// Tournament
	population = tournament(population, 3);
	// Make cyclic crossover and generate children
	population = cyclicCrossover(population);
	// Avaliate children
	population = evaluateChildren(population);
	printPopulation(population);

	return 0;
}


int **generateIndividuals(int **population) {
	time_t t;
	bool arr[ISIZE];
	int i, j;

	srand((unsigned)time(&t));	

	for(i=0; i<PSIZE; i++) {
		memset(arr, 0, sizeof(arr));
		for(int j=0;j < ISIZE; j++) {
			int r = rand() % 10;
			if(!arr[r])
				population[i][j] = r;
			else j--;
			arr[r] = 1;
		}
	}

	return population;
}


int **evaluatePopulation(int **population) {
	int i, send, more, money;

	for(i=0; i<PSIZE; i++) {
		send = more = money = 0;
		send = population[i][0]*1000+population[i][1]*100+population[i][2]*10+population[i][3];
		more = population[i][4]*1000+population[i][5]*100+population[i][6]*10+population[i][1];
		money = population[i][4]*10000+population[i][5]*1000+population[i][2]*100+population[i][1]*10+population[i][7];
		// Set evaluation value for the i'th individual
		population[i][ISIZE] = abs((send + more) - money);
	}

	return population;
}

int **evaluateChildren(int **population) {
	int i, send, more, money;

	for(i=100; i<180; i++) {
		send = more = money = 0;
		send = population[i][0]*1000+population[i][1]*100+population[i][2]*10+population[i][3];
		more = population[i][4]*1000+population[i][5]*100+population[i][6]*10+population[i][1];
		money = population[i][4]*10000+population[i][5]*1000+population[i][2]*100+population[i][1]*10+population[i][7];
		// Set evaluation value for the i'th individual
		population[i][ISIZE] = abs((send + more) - money);
	}

	return population;
}

void maxMinEval(int **population) {
	int min, max;
	min = max = population[0][ISIZE];

	for(int i=1; i<PSIZE; i++) {
		if(population[i][ISIZE] < min) min = population[i][ISIZE];
		if(population[i][ISIZE] > max) max = population[i][ISIZE];
	}

	printf("Max eval value: %d\n", max);
	printf("Min eval value: %d\n", min);
	
	return;
}


void mean(int **population) {
	unsigned long int sum = 0;

	for(int i=0; i<PSIZE; i++)
		sum += population[i][ISIZE];

	printf("Mean: %ld\n", sum/PSIZE); 
	
	return; 
}

// Copy selected fathers to positions 101 to 180
int **tournament(int **population, int tour) {
	time_t t;
	int i,j , bestIndex, randInt;
	int best;

	srand((unsigned)time(&t));

	for(i=100; i<180; i++) {
		best = 1000000;
		// Make one tornament based on tour
		for(j=0; j<tour; j++) {
			randInt = rand() % PSIZE;
			if(population[randInt][ISIZE] < best) {
				best = population[randInt][ISIZE];
				bestIndex = randInt;
			}
		}
		// Copy winner to i'th row of population
		for(j=0; j<ISIZE+1; j++) {
			population[i][j] = population[bestIndex][j];
		}
	}

	return population;
}

void printPopulation(int **population) {
	int i, j;
	for(i=0; i<180; i++) {
		if(i%99 == 0) printf("\n");
		for(j=0; j<11; j++)
			printf("%2d ", population[i][j]);
		printf("\n");
	}
	return;
}

int **cyclicCrossover(int **population) {
	time_t t;
	int i, j, randInt, randIndex, temp;

	srand((unsigned)time(&t));

	for(i=100; i<180; i+=2) {
		randIndex = rand()%10;
		randInt = population[i][randIndex];	
	
		while(population[i+1][randIndex] != randInt) {	
			temp = population[i+1][randIndex];
			population[i+1][randIndex] = population[i][randIndex];
			population[i][randIndex] = temp;
			for(j=0; j<10; j++) {
				if(j != randIndex && population[i][j] == temp) {
					randIndex = j;
					randInt = population[i+1][j];
				}
			}
		}
	}

	return population;
}
