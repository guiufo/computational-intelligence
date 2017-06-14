#include "types.h"

//
Population* cyclicCrossover(Population *population, float cross) {
  int i, j, temp;
  int tempIndex, initialValue, nextValue;
  int psize = population->psize;

  // Makes a crossover in selected fathers
  for(i=(int)psize-cross*psize; i<psize-1; i+=2) {
      tempIndex = rand()%10;
      initialValue = population->individuals[i].cromossome[tempIndex];

      while(population->individuals[i+1].cromossome[tempIndex] != initialValue) {
        nextValue = population->individuals[i+1].cromossome[tempIndex];
        for(j=0; j<10; j++) {
          if(j != tempIndex && population->individuals[i].cromossome[j] == nextValue) {
            temp = population->individuals[i+1].cromossome[tempIndex];
            population->individuals[i+1].cromossome[tempIndex] = population->individuals[i].cromossome[tempIndex];
            population->individuals[i].cromossome[tempIndex] = temp;
            tempIndex = j;
            break;
          }
        }
      }
      temp = population->individuals[i+1].cromossome[tempIndex];
      population->individuals[i+1].cromossome[tempIndex] = population->individuals[i].cromossome[tempIndex];
      population->individuals[i].cromossome[tempIndex] = temp;
  }

  return population;
}
