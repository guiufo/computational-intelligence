#include "types.h"
#include "helperFunctions.c"
#include "evaluationFunctions.c"
#include "mutationFunctions.c"
#include "crossoverFunctions.c"

void experiment(int populationSize, double mutationRate, int diseaseClass);
// 50 individuals and 50 generations, Stochastic roulette selection
// 100% crossover rate, elitism of the best father
int main() {
  srand(time(NULL));
  experiment(10, 0.3, 1);
  return 0;
}

void experiment(int populationSize, double mutationRate, int diseaseClass) {
  int i, j;
  Population *population;
  population = initPopulation(population, populationSize);
  Data* data = getData(diseaseClass);

  // Fitness of all population
  for(i=0; i<populationSize; i++) {
    population->individuals[i] = fitness(population->individuals[i], data, diseaseClass);
  }

  showPopulation(population);

  for(i=0; i<populationSize; i++) {
    population->individuals[i] = mutate(population->individuals[i], mutationRate);
  }

  printf("\n");
  showPopulation(population);
  printf("\n");

  population = crossover(population);
  showPopulation(population);

}
