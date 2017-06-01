#include "functions.h"

Population* mutate(Population *population, int rate);

Population* mutate(Population *population, int rate) {
  time_t t;
  int i, randColumnA, randColumnB, temp;

  srand((unsigned)time(&t));

  for(i=0; i < population->populationSize; i++) {
    if(rand()%100 <= rate) {
      randColumnA = rand() % 10;
      randColumnB = rand() % 10;
      temp = population->individuals[i].pvector[randColumnA];
      population->individuals[i].pvector[randColumnA] = population->individuals[i].pvector[randColumnB];
      population->individuals[i].pvector[randColumnB] = temp;
    }
  }

  return population;
}
