#include "functions.h"

// Makes a cyclicCrossover in all given population
Population* cyclicCrossover(Population *population, int cross) {
  time_t t;
  int i, j, temp;
  int tempIndex, initialValue, nextValue;

  for(i=0; i < (population->populationSize)-1; i+=2) {
      srand((unsigned)time(&t));
      tempIndex = rand()%10;
      initialValue = population->individuals[i].pvector[tempIndex];

      while(population->individuals[i+1].pvector[tempIndex] != initialValue) {
        nextValue = population->individuals[i+1].pvector[tempIndex];
        for(j=0;j<10;j++) {
          if(j != tempIndex && population->individuals[i].pvector[j] == nextValue) {
            temp = population->individuals[i+1].pvector[tempIndex];
            population->individuals[i+1].pvector[tempIndex] = population->individuals[i].pvector[tempIndex];
            population->individuals[i].pvector[tempIndex] = temp;
            tempIndex = j;
            break;
          }
        }
      }
      temp = population->individuals[i+1].pvector[tempIndex];
      population->individuals[i+1].pvector[tempIndex] = population->individuals[i].pvector[tempIndex];
      population->individuals[i].pvector[tempIndex] = temp;
  }

  return population;
}
