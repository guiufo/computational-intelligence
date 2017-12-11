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

int makeExperiment( \
  int problem, int popsize, int generations, int tour, float cross, float mutation) {

  // Init random population and evaluate individuals
  Population *population;
  population = (Population*) malloc(sizeof(Population));
  population = initPopulation(population, popsize);
  switch(problem) {
    case 1:
      population = evaluateSendPopulation(population);
      break;
    case 2:
      population = evaluateEatPopulation(population);
      break;
    case 3:
      population = evaluateCrossPopulation(population);
      break;
    case 4:
      population = evaluateCocaPopulation(population);
      break;
    case 5:
      population = evaluateDonaldPopulation(population);
      break;
  };

  // Run n generations
  for(int i = 0; i < generations; i++) {
    // Verify if solution is found
    if(population->individuals[0].fitness == 0){
      printf("Uma solução foi encontrada!\n");
      showPopulation(population);
      free(population);
      return 1;
    }
    population = sortPopulation(population);
    // population = tournament(population, tour, cross);
    // population = roulette(population, cross);
    population = stochasticRoulette(population, cross, tour);
    population = cyclicCrossover(population, cross);
    population = mutate(population, mutation, cross);
    switch(problem) {
      case 1:
        population = evaluateSendPopulation(population);
        break;
      case 2:
        population = evaluateEatPopulation(population);
        break;
      case 3:
        population = evaluateCrossPopulation(population);
        break;
      case 4:
        population = evaluateCocaPopulation(population);
        break;
      case 5:
        population = evaluateDonaldPopulation(population);
        break;
    };
  }
  free(population);
  return 0;
}

// Arguments: n experiments, pop size, n generations, tour size, cross tax, mut tax
int main(int argc, char* argv[]) {
  int counter = 0;
  time_t t;
  srand(time(&t));

  for(int i=0; i<atoi(argv[1]); i++)
    counter += makeExperiment( \
      atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), \
      atoi(argv[5]), atof(argv[6]), atof(argv[7]));
  printf("%d\n", counter);

  return 0;
}
