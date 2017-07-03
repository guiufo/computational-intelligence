#include "types.h"
#include "helperFunctions.c"
#include "evaluationFunctions.c"

// 50 individuals and 50 generations, Stochastic roulette selection
// 100% crossover rate, elitism of the best father

int makeExperiment() {
  return 0;
}

int main() {
  srand(time(NULL));
  int i, j;
  int diseaseClass = 1;
  Population *population;
  population = initPopulation(population, 50);
  int** data = getData();

  // Fitness of all population
  for(i=0; i<50; i++) {
    population->individuals[i] = fitness(population->individuals[i], data, diseaseClass);
  }

  showPopulation(population);

  return 0;
}
