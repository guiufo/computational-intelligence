// Send More Money Problem
// Genetic Algorithms Approach
// Author: Guilherme Martini
// Date: 14 April 2017

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>

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
	int **population;
	int i, j, sucessCount;

	sucessCount = 0;

	// Allocate matrix for population
	// Each row from index 0 to 7 corresponds to "sendmory"
	population = (int**) malloc(180 * sizeof(int*));
	for(i=0; i < 180; i++) {
		population[i] = (int*) malloc(11 * sizeof(int));
	}

	// 1000 experiments
	for(j=0; j<1; j++) {
		// Generate random population
		population = generateIndividuals(population);
		population = evaluatePopulation(population);
		printPopulation(population);

		// 200 generations
		for(i=0; i<1; i++) {
			if(sucess(population)) {
				sucessCount += 1;
				printPopulation(population);
			}
			population = tournament(population, 3);
			population = cyclicCrossover(population);
			population = mutation(population);
			population = evaluatePopulation(population);
			population = sortPopulation(population);
			printPopulation(population);
		}
	}

	free(population);
	printf("Sucess count: %d \n", sucessCount);

	return 0;
}


int sucess(int **population) {
	for(int i=0; i<100; i++)
		if(population[i][10] == 0) return 1;
	return 0;
}

int **generateIndividuals(int **population) {
	time_t t;
	int arr[10];
	int i, j, r;

	srand((unsigned)time(&t));	

	// Fill matrix with 0s
	for(i=0; i<180; i++) {
		for(j=0; j<11; j++)
			population[i][j] = 0;
	}

	for(i=0; i<100; i++) {
		for(j=0; j<10; j++)
			arr[j] = 0;
		for(j=0; j<10; j++) {
			r = rand() % 10;
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
		population[i][10] = abs((send + more) - money);
	}

	return population;
}


void maxMinEval(int **population) {
	int min, max;
	min = max = population[0][10];

	for(int i=1; i<180; i++) {
		if(population[i][10] < min) min = population[i][10];
		if(population[i][10] > max) max = population[i][10];
	}

	printf("Max eval value: %d\n", max);
	printf("Min eval value: %d\n", min);
	
	return;
}


void mean(int **population) {
	int sum = 0;

	for(int i=0; i<180; i++)
		sum += population[i][10];

	printf("Mean: %d\n", sum/180); 
	
	return; 
}

// Copy selected fathers to positions 101 to 180
int **tournament(int **population, int tour) {
	time_t t;
	int i, j, bestIndex, randInt;
	int best, temp; 

	srand((unsigned)time(&t));

	for(i=100; i<180; i++) {
		best = 1000000;
		// Make one tournament based on tour
		for(j=0; j<tour; j++) {
			randInt = rand() % 100;
			if(population[randInt][10] < best) {
				best = population[randInt][10];
				bestIndex = randInt;
			}
		}
		// Copy winner to i'th row of population
		for(j=0; j<11; j++) {
			temp = population[i][j];
			population[i][j] = population[bestIndex][j];
			population[bestIndex][j] = temp;
		}
			
	}

	return population;
}

void printPopulation(int **population) {
	int i, j;
	for(i=0; i<180; i++) {
		if(i != 0 && i%100 == 0) printf("--------------------------------> Children from here\n");
		for(j=0; j<11; j++)
			printf("%2d ", population[i][j]);
		printf("\n");
	}
	printf("\n");
	
	return;
}

int **cyclicCrossover(int **population) {
	time_t t;
	int i, j, temp;
	int randIndex, nextValue, initialValue;
	int indexes[10] = {0};

	srand((unsigned)time(&t));

	for(i=100; i<179; i+=2) {
		randIndex = rand()%10;
		indexes[randIndex] = 1;
		initialValue = population[i][randIndex];

		while(population[i+1][randIndex] != initialValue) {
			nextValue = population[i+1][randIndex];

			for(j=0;j<10;j++) { 
				if(population[i][j] == nextValue) {
					randIndex = j;
					indexes[randIndex] = 1;
				}
			}
		}

		for(j=0;j<10;j++) {
			if(indexes[j]) {
				temp = population[i][j];
				population[i][j] = population[i+1][j];
				population[i+1][j] = temp;
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
		randColumn = rand() % 8;
		// Swap genes
		temp = population[randRow][8];
		population[randRow][8] = population[randRow][randColumn];
		population[randRow][randColumn] = temp;
	}

	return population;
}

int **sortPopulation(int **population) {
	int i, j, r;
	int *temp;
	
	// Temp vector to swap rows of matrix
	temp = (int*) malloc(sizeof(int)*11);
	
	// Insertion sort	
	for(i=1; i < 180; i++) {
		j = i;
		while(j>0 && population[j][10] < population[j-1][10]) {
			memcpy(temp, population[j], sizeof(int)*11);
			memcpy(population[j], population[j-1], sizeof(int)*11);
			memcpy(population[j-1], temp, sizeof(int)*11);
			j--;
		}
	}	
			
	free(temp);	
	return population;
}
