#include "types.h"

Population* tournament(Population *population, int tourSize, float cross);
Population* roulette(Population *population, float cross);
Population* stochasticRoullete(Population *population, float cross, int tourSize);

// Receives a sorted population to maintain elitism
Population* tournament(Population *population, int tourSize, float cross) {
	int i, j, best, bestIndex, randInt;
  int psize = population->psize;
  Population *crossPopulation;
  // Get number of bytes allocated by population
  int prealsize =  psize*sizeof(Individual)+sizeof(Population);

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
		crossPopulation->individuals[i] = population->individuals[bestIndex];
	}

  // Return the winners population with elitism
	return crossPopulation;
}

Population* roulette(Population *population, float cross) {
  int i, j, fsum, psize, prealsize;
  float *probvector;
  float randDouble, psum;
  Population *crossPopulation;

  psize = population->psize;
  // Get number of bytes allocated by population
  prealsize =  psize*sizeof(Individual)+sizeof(Population);
  crossPopulation = (Population *) malloc(sizeof(Population));
  crossPopulation->individuals = malloc(psize*sizeof(Individual));
  // Create hard copy of population
  memcpy(crossPopulation, population, prealsize);

  fsum = psum = 0;
  probvector = malloc(psize*sizeof(int));

  // Fitness sum
  for(i=0; i<psize; i++){
      fsum += population->individuals[i].fitness;
  }
  // Generate probabilites for each individual
  for(i=0; i<psize; i++){
    probvector[i] = psum + (float)population->individuals[i].fitness / fsum;
    psum += probvector[i];
  }
  // Fill temp population with winners
	for(i=(int)psize-cross*psize; i<psize; i++) {
    randDouble = (double)rand()/(double)RAND_MAX;
    for(j=0; j<psize-1; j++) {
      if(randDouble > probvector[j] && randDouble < probvector[j+1]) {
    		crossPopulation->individuals[i] = population->individuals[j];
        break;
      }
    }
  }

  return crossPopulation;

}

Population* stochasticRoullete(Population *population, float cross, int tourSize) {

	return population;
}
