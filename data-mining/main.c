#include "types.h"
#include "helperFunctions.c"

int main() {
  Population *population;

  population = malloc(sizeof(Population));
  population = initPopulation(population, 10);
  showFullPopulation(population);
  // population = crossover(population);
  //showFullPopulation(population);

  return 0;
}
