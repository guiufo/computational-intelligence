#include "functions.h"

Population* initPopulation(Population *population, int populationSize);
Population* sortPopulation(Population *population);
void showPopulation(Population *population);

// Init a random population of given size
Population* initPopulation(Population *population, int populationSize) {
  int i, j, temp, tempRand;
  population->populationSize = populationSize;
  population->individuals = malloc(populationSize * sizeof(Individual));
  srand(time(NULL));
  for(i=0; i < populationSize; i++){
    for(j=0;j<10;j++){
      population->individuals[i].pvector[j] = j;
    }
    for(j=0; j<10; j++) {
      temp = population->individuals[i].pvector[j];
      tempRand = rand()%10;
      population->individuals[i].pvector[j] = population->individuals[i].pvector[tempRand];
      population->individuals[i].pvector[tempRand] = temp;

    }
    population->individuals[i].evaluation = 0;
  }
  return population;
}

// Insert sort given population by evaluation
Population* sortPopulation(Population *population) {
  int i, j;
	Individual tempIndividual;
	for(i=1; i < population->populationSize; i++) {
		j = i;
		while(j>0 && population->individuals[j].evaluation < population->individuals[j-1].evaluation) {
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
  for(int i = 0; i < population->populationSize; i++){
    if(i%10 == 0) printf("\n");
    for(int j = 0; j < 10; j++) {
      printf("%d ", population->individuals[i].pvector[j]);
    }
    printf(" %d\n", population->individuals[i].evaluation);
  }
}
