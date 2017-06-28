#include "types.h"
#include "helperFunctions.c"

// 50 individuals and 50 generations, Stochastic roulette selection
// 100% crossover rate, elitism of the best father

int makeExperiment() {
  return 0;
}

int main() {
  srand(time(NULL));
  Population *population;
  population = initPopulation(population, 50);
  // Get a 358 X 35 matrix
  // 238 for training, 120 for testing
  //int** data = getDermatologyData();

  // population = fitness(population);

  showPopulation(population);

  return 0;
}
