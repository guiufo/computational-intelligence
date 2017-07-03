#include "types.h"

Population* crossover(Population *population) {
  int i, j, point1, point2;

  for(i=0; i < population->size; i+=2) {
    point1 = rand() % 33;
    point2 = rand() % 33;

    if(point1 > point2) {
    }
    else if(point1 < point2) {
    }

  }

  return population;
}
