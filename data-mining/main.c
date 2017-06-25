#include "types.h"
#include "helperFunctions.c"

// 50 individuals and 50 generations, Stochastic roulette selection
// 100% crossover rate, elitism of the best father

int makeExperiment(Population *population, int populationSize, int generations) {

  return 0;
}

int main() {
  Population *population;
  population = initPopulation(population, 10);
  int** data = getDermatologyData();

  showPopulation(population);
  // population = crossover(population);
  //showFullPopulation(population);

  //showDermatologyData(data);

  return 0;
}
