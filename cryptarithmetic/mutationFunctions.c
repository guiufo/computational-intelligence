#include "types.h"

Population* mutate(Population *population, float mutation, float cross) {
  int i, randColumnA, randColumnB, temp;
  int psize = population->psize;
  float randDouble;

  // Mutate children of selected fathers
  for(i=(int)psize-psize*cross; i<psize; i++) {
    randDouble = (double)rand()/(double)RAND_MAX;
    if(randDouble <= mutation) {
      randColumnA = rand() % 10;
      randColumnB = rand() % 10;
      // Swap two values in cromossome
      temp = population->individuals[i].cromossome[randColumnA];
      population->individuals[i].cromossome[randColumnA] = population->individuals[i].cromossome[randColumnB];
      population->individuals[i].cromossome[randColumnB] = temp;
    }
  }

  return population;
}
