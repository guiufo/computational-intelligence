#include "functions.h"

Population* tournament(Population *population, int tourSize, int cross) {
  time_t t;
	int i, j, best, bestIndex, randInt;
  Population *tempPopulation;

  tempPopulation = (Population *) malloc(sizeof(Population));
  *tempPopulation = *population;

	srand((unsigned)time(&t));

	for(i=0; i< cross; i++) {
		best = 1000000000;
		// Make one tournament based on tour
		for(j=0; j<tourSize; j++) {
			randInt = rand() % population->populationSize;
			if(population->individuals[randInt].evaluation < best) {
				best = population->individuals[randInt].evaluation;
				bestIndex = randInt;
			}
		}
		// Copy winner to i'th row of temp population
		for(j=0; j<11; j++) {
			tempPopulation->individuals[j] = population->individuals[bestIndex];
		}

	}

	return tempPopulation;
}
