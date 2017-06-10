#include "types.h"

// Functions signatures
Population* initPopulation(Population *population, int psize);
Population* sortPopulation(Population *population);
void showPopulation(Population *population);

// Init a random population of given size
Population* initPopulation(Population *population, int psize) {
  time_t t;
  srand((unsigned)time(&t));
  int i, j, temp, tempRand;

  population->psize = psize;
  population->individuals = malloc(psize * sizeof(Individual));
  for(i=0; i < psize; i++){
    for(j=0;j<10;j++){
      population->individuals[i].dna[j] = j;
    }
    for(j=0; j<10; j++) {
      temp = population->individuals[i].dna[j];
      tempRand = rand()%10;
      population->individuals[i].dna[j] = population->individuals[i].dna[tempRand];
      population->individuals[i].dna[tempRand] = temp;

    }
    population->individuals[i].fitness = 0;
  }
  return population;
}

// Insert sort given population by fitness
Population* sortPopulation(Population *population) {
  int i, j;
	Individual tempIndividual;
	for(i=1; i < population->psize; i++) {
		j = i;
		while(j>0 && population->individuals[j].fitness < population->individuals[j-1].fitness) {
			tempIndividual = population->individuals[j];
			population->individuals[j] = population->individuals[j-1];
			population->individuals[j-1] = tempIndividual;
			j--;
		}
	}

	return population;
}

// Print population
void showPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < 10; j++) {
      printf("%d ", population->individuals[i].dna[j]);
    }
    printf(" %d\n", population->individuals[i].fitness);
  }
}
