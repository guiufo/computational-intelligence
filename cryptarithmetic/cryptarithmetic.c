#include "helperFunctions.c"
#include "evaluationFunctions.c"
#include "selectionFunctions.c"
#include "crossoverFunctions.c"
#include "mutationFunctions.c"

/*--------------- Functions Signatures and Types -----------------
Population* initPopulation(Population *population, int psize);
Population* sortPopulation(Population *population);
void showPopulation(Population *population);
Population* tournament(Population *population, int tourSize, float cross);
Population* cyclicCrossover(Population *population, float cross);
Population* mutate(Population *population, float mutation, float cross);

typedef struct individual {
	// permutation vector
  int cromossome[10];
	int fitness;
}Individual;

typedef struct population {
	Individual *individuals;
	int psize;
}Population;
*/

int makeExperiment(int popsize, int generations, int tour, float cross, float mutation) {
  // Init random population and evaluate individuals
  Population *population;
  population = (Population*) malloc(sizeof(Population));
  population = initPopulation(population, popsize);
  population = evaluateSendPopulation(population);

  // Run n generations
  for(int i = 0; i < generations; i++) {
    // Verify if solution is found
    if(population->individuals[0].fitness == 0){
      free(population);
      return 1;
    }
    population = sortPopulation(population);
    // population = tournament(population, tour, cross);
    population = roulette(population, cross);
    population = cyclicCrossover(population, cross);
    population = mutate(population, mutation, cross);
    population = evaluateSendPopulation(population);
  }
  free(population);
  return 0;
}

int main() {
  int counter = 0;
  time_t t;
  srand(time(&t));

  for(int i=0; i<100; i++)
    counter += makeExperiment(100, 200, 3, 0.8, 0.1);
  printf("%d\n", counter);

  return 0;
}
