#include "types.h"

Population* mutate(Population *population, float mutation, float cross) {
  time_t t;
  srand((unsigned)time(&t));
  int i, randColumnA, randColumnB, temp;
  int psize = population->psize;
  float randFloat;

  // Mutate children of selected fathers
  for(i=(int)psize-psize*cross; i<psize; i++) {
    randFloat = (double)rand()/(double)RAND_MAX;
    if(randFloat <= mutation) {
      randColumnA = rand() % 10;
      randColumnB = rand() % 10;
      // Swap two values in dna
      temp = population->individuals[i].dna[randColumnA];
      population->individuals[i].dna[randColumnA] = population->individuals[i].dna[randColumnB];
      population->individuals[i].dna[randColumnB] = temp;
    }
  }

  return population;
}
