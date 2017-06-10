#include "types.h"

// Receives a sorted population to maintain elitism
Population* tournament(Population *population, int tourSize, float cross) {
  time_t t;
	srand((unsigned)time(&t));
	int i, j, best, bestIndex, randInt;
  int psize = population->psize;
  Population *crossPopulation;
  // Get number of bytes allocated by population
  int prealsize =  psize*sizeof(Individual)+sizeof(int);

  // Create hard copy of population
  crossPopulation = (Population *) malloc(sizeof(Population));
  crossPopulation->individuals = malloc(psize*sizeof(Individual));
  memcpy(crossPopulation, population, prealsize);

  // Makes a tournament and copy after remaining best individuals
	for(i=(int)psize-cross*psize; i<psize; i++) {
		best = BIGINT;
		// Make one tournament based on tour
		for(j=0; j<tourSize; j++) {
      // Select random individual
			randInt = rand() % psize;
			if(population->individuals[randInt].fitness < best) {
				best = population->individuals[randInt].fitness;
				bestIndex = randInt;
			}
		}
		// Copy winner to i'th row of temp population
		for(j=0; j<11; j++) {
			crossPopulation->individuals[j] = population->individuals[bestIndex];
		}
	}
  // Return the winners population with elitism
	return crossPopulation;
}
