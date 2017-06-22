#include "types.h"

// Functions signatures
Population* initPopulation(Population *population, int psize);
void showPopulation(Population *population);

// Init a random population of given size
Population* initPopulation(Population *population, int psize) {
  int i, j, temp, tempRand;

  population->psize = psize;
  population->individuals = malloc(psize * sizeof(Individual));
  for(i=0; i < psize; i++){
    for(j=0;j<32;j++){
      population->individuals[i].cromossome[j][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[j][1] = rand() % 2;
      population->individuals[i].cromossome[j][2] = rand() % 4;
      population->individuals[i].nominal = 0;
    }
      // age from 0 to 100
      population->individuals[i].cromossome[32][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[32][1] = rand() % 2 + 2;
      population->individuals[i].cromossome[32][2] = rand() % 100;
      population->individuals[i].nominal = 1;

      // family history
      population->individuals[i].cromossome[33][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[33][1] = rand() % 2 + 2;
      population->individuals[i].cromossome[33][2] = rand() % 2;
      population->individuals[i].nominal = 1;
  }
  return population;
}

// Insert sort given population by fitness
/*
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

// Print population functions
void showPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < 5; i++){
    for(j = 0; j < 10; j++) {
      printf("%d ", population->individuals[i].cromossome[j]);
    }
    printf(" %d\n", population->individuals[i].fitness);
  }
  printf("\n");
  printf("    .    .    .\n");
  printf("    .    .    .\n");
  printf("    .    .    .\n");
  printf("\n");
  for(i = population->psize-5; i < population->psize; i++){
    for(j = 0; j < 10; j++) {
      printf("%d ", population->individuals[i].cromossome[j]);
    }
    printf(" %d\n", population->individuals[i].fitness);
  }
}
*/

void showFullPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < 34; j++) {
      printf("%.2f %.0f %.0f|", population->individuals[i].cromossome[j][0],
      population->individuals[i].cromossome[j][1], population->individuals[i].cromossome[j][2]);
    }
    printf("\n");
    printf("\n");
  }
}
