#include "types.h"
#include "helperFunctions.c"
#include "evaluationFunctions.c"
#include "mutationFunctions.c"

int experiment(int populationSize, double mutationRate, int diseaseClass);
// 50 individuals and 50 generations, Stochastic roulette selection
// 100% crossover rate, elitism of the best father
int main() {
  srand(time(NULL));
  experiment(10, 0.3, 1);
  return 0;
}

int experiment(int populationSize, double mutationRate, int diseaseClass) {
  int i, j;
  Population *population;
  population = initPopulation(population, populationSize);
  int** data = getData();

  // Fitness of all population
  for(i=0; i<populationSize; i++) {
    population->individuals[i] = fitness(population->individuals[i], data, diseaseClass);
  }

  showPopulation(population);

  for(i=0; i<populationSize; i++) {
    population->individuals[i] = mutate(population->individuals[i], mutationRate);
  }
  printf("\n");
  printf("\n");
  showPopulation(population);

  return 0;
}
