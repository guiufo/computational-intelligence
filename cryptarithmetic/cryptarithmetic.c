#include "helperFunctions.c"
#include "evaluationFunctions.c"
#include "selectionFunctions.c"
#include "crossoverFunctions.c"
#include "mutationFunctions.c"

/*--------------- Functions Signatures and Types -----------------
Population* initPopulation(Population *population, int psize );
Population* sortPopulation(Population *population);
void showPopulation(Population *population);
Population* tournament(Population *population, int tourSize, float cross);
Population* cyclicCrossover(Population *population, float cross);
Population* mutate(Population *population, float mutation);

typedef struct individual {
	// permutation vector
  int dna[10];
	int fitness;
}Individual;

typedef struct population {
	Individual *individuals;
	int psize;
}Population;
*/

void makeExperiment(int popsize, int generations, float cross, int tour) {
  // Init random population and evaluate individuals
  Population *population;
  population = (Population*) malloc(sizeof(Population));
  population = initPopulation(population, popsize);
  population = evaluateSendPopulation(population);

  // Run n generations
  for(int i = 0; i < generations; i++) {
    population = tournament(population, tour, cross);
    population = cyclicCrossover(population, cross);
    population = evaluateSendPopulation(population);
    population = sortPopulation(population);
    showPopulation(population);
  }
}

int main() {
  makeExperiment(20, 3, 0.8, 3);

  return 0;
}
