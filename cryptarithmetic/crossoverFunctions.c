#include "types.h"

//
Population* cyclicCrossover(Population *population, float cross) {
  time_t t;
  srand((unsigned)time(&t));
  int i, j, temp;
  int tempIndex, initialValue, nextValue;
  int psize = population->psize;

  // Makes a crossover in selected fathers
  for(i=(int)psize-cross*psize; i<psize-1; i+=2) {
      tempIndex = rand()%10;
      initialValue = population->individuals[i].dna[tempIndex];

      while(population->individuals[i+1].dna[tempIndex] != initialValue) {
        nextValue = population->individuals[i+1].dna[tempIndex];
        for(j=0; j<10; j++) {
          if(j != tempIndex && population->individuals[i].dna[j] == nextValue) {
            temp = population->individuals[i+1].dna[tempIndex];
            population->individuals[i+1].dna[tempIndex] = population->individuals[i].dna[tempIndex];
            population->individuals[i].dna[tempIndex] = temp;
            tempIndex = j;
            break;
          }
        }
      }
      temp = population->individuals[i+1].dna[tempIndex];
      population->individuals[i+1].dna[tempIndex] = population->individuals[i].dna[tempIndex];
      population->individuals[i].dna[tempIndex] = temp;
  }

  return population;
}
