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
int **mutation(int **population);
int **sortPopulation(int **population);
int sucess(int **population);

void maxMinEval(int **population);
void mean(int **population);
void printPopulation(int **population);


int main(int argc, char *argv[]) {
	int **population, i, j;
	int nrows, ncolumns, sucessCount;

	// Total size of population plus space for children
	nrows = PSIZE + PSIZE*PCROSS;
	// 8 for individual, 2 for permutation, 1 for fitness score
	ncolumns = ISIZE + 1;

	/*
	// Allocate matrix for population
	// Each row from index 0 to 7 corresponds to "sendmory"
	population = (int**) malloc(nrows * sizeof(int*));
	for(i=0; i < nrows; i++)
		population[i] = (int*) malloc(ncolumns * sizeof(int));

	// Generate random population
	population = generateIndividuals(population);
	// Evaluate each individual
	population = evaluatePopulation(population);
	*/
	
	sucessCount = 0;

	for(j=0; j<1000; j++) {
		// Allocate matrix for population
		// Each row from index 0 to 7 corresponds to "sendmory"
		population = (int**) malloc(nrows * sizeof(int*));
		for(i=0; i < nrows; i++)
			population[i] = (int*) malloc(ncolumns * sizeof(int));

		// Generate random population
		population = generateIndividuals(population);
		// Evaluate each individual
		population = evaluatePopulation(population);

		for(i=0; i<200; i++) {
			// Tournament
			population = tournament(population, 3);
			// Make cyclic crossover and generate children
			population = cyclicCrossover(population);
			// Make mutations
			population = mutation(population);
			// Avaliate children
			population = evaluatePopulation(population);
			population = sortPopulation(population);
		}
		sucessCount += sucess(population);
	}

	printPopulation(population);
	// Print max and min evaluation values
	maxMinEval(population);	
	// Calculate and print the mean of evals
	mean(population);
	printf("Percent of sucess in 1000 experiments: %d \n", 1000/sucessCount);

	return 0;
}

int sucess(int **population) {
	for(int i=0; i<180; i++)
		if(population[i][10] == 0) return 1;
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

	for(i=0; i<180; i++) {
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
		// Make one tournament based on tour
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
		// Select crossover point and get value
		randIndex = rand()%10;
		randInt = population[i][randIndex];	
	
		// Make a cyclic crossover
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

int **mutation(int **population) {
	time_t t;
	int i, randRow, randColumn, temp;

	srand((unsigned)time(&t));

	// Select 10% of generated children	
	for(i=0; i<8; i++) {
		// Select row to mutate
		randRow = (rand() % 80) + 100;
		// Select gene to mutate
		randColumn = rand() % 7;
		// Swap genes
		temp = population[randRow][9];
		population[randRow][9] = population[randRow][randColumn];
		population[randRow][randColumn] = temp;
	}

	return population;
}

int **sortPopulation(int **population) {
	int i, j;
	int *temp;
	
	// Temp vector to swap rows of matrix
	temp = (int*) malloc(sizeof(int)*11);
	
	// Insertion sort	
	for(i=1; i < 180; i++) {
		j = i;
		while(j>0 && population[j][10] < population[j-1][10]) {
			//temp = population[j];
			//population[j] = population[j-1];
			//population[j-1] = temp;
			memcpy(temp, population[j], sizeof(int)*11);
			memcpy(population[j], population[j-1], sizeof(int)*11);
			memcpy(population[j-1], temp, sizeof(int)*11);
			j--;
		}
	}	
			
	free(temp);	
	return population;
}
