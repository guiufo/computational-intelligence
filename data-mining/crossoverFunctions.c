#include "types.h"

Population* crossover(Population *population) {
  int i, j, point1, point2;
  Base tempBase;

  for(i=0; i < population->psize; i+=2) {
    point1 = rand() % 33;
    point2 = rand() % 33;

    if(point1 > point2) {
      for(j=point2; j<point1; j++){
        tempBase = population->individuals[i].cromossome[j];
        population->individuals[i].cromossome[j] = population->individuals[i+1].cromossome[j];
        population->individuals[i+1].cromossome[j] = tempBase;
      }
    }
    else if(point1 < point2) {
      for(j=point1; j<point2; j++){
        tempBase = population->individuals[i].cromossome[j];
        population->individuals[i].cromossome[j] = population->individuals[i+1].cromossome[j];
        population->individuals[i+1].cromossome[j] = tempBase;
      }
    }
  }

  return population;
}
