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
  Population *population2;
  Population *population3;
  population = (Population*) malloc(sizeof(Population));
  population2 = (Population*) malloc(sizeof(Population));
  population3 = (Population*) malloc(sizeof(Population));

  population = initPopulation(population, popsize/2);
  population2 = initPopulation(population2, popsize/2);

  switch(problem) {
    case 1:
      population = evaluateSendPopulation(population);
      population2 = evaluateSendPopulation(population2);
      break;
    case 2:
      population = evaluateEatPopulation(population);
      population2 = evaluateEatPopulation(population2);
      break;
    case 3:
      population = evaluateCrossPopulation(population);
      population2 = evaluateCrossPopulation(population2);
      break;
    case 4:
      population = evaluateCocaPopulation(population);
      population2 = evaluateCocaPopulation(population2);
      break;
    case 5:
      population = evaluateDonaldPopulation(population);
      population2 = evaluateDonaldPopulation(population2);
      break;
  };

  // Run n generations
  for(int i = 0; i < generations/5; i++) {
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

    for(int i = 0; i < generations/5; i++) {
    // Verify if solution is found
    if(population2->individuals[0].fitness == 0){
      printf("Uma solução foi encontrada!\n");
      showPopulation(population2);
      free(population2);
      return 1;
    }
    population2 = sortPopulation(population2);
    // population2 = tournament(population2, tour, cross);
    // population2 = roulette(population2, cross);
    population2 = stochasticRoulette(population2, cross, tour);
    population2 = cyclicCrossover(population2, cross);
    population2 = mutate(population2, mutation, cross);
    switch(problem) {
      case 1:
        population2 = evaluateSendPopulation(population2);
        break;
      case 2:
        population2 = evaluateEatPopulation(population2);
        break;
      case 3:
        population2 = evaluateCrossPopulation(population2);
        break;
      case 4:
        population2 = evaluateCocaPopulation(population2);
        break;
      case 5:
        population2 = evaluateDonaldPopulation(population2);
        break;
    };
  }
    // TODO: mesclar populacoes na populacao 3



    // TODO: float to int
    for(int i = 0; i < (generations*3/5); i++) {
    // Verify if solution is found
    if(population3->individuals[0].fitness == 0){
      printf("Uma solução foi encontrada!\n");
      showPopulation(population3);
      free(population3);
      return 1;
    }
    population3 = sortPopulation(population3);
    // population3 = tournament(population3, tour, cross);
    // population3 = roulette(population3, cross);
    population3 = stochasticRoulette(population3, cross, tour);
    population3 = cyclicCrossover(population3, cross);
    population3 = mutate(population3, mutation, cross);
    switch(problem) {
      case 1:
        population3 = evaluateSendPopulation(population3);
        break;
      case 2:
        population3 = evaluateEatPopulation(population3);
        break;
      case 3:
        population3 = evaluateCrossPopulation(population3);
        break;
      case 4:
        population3 = evaluateCocaPopulation(population3);
        break;
      case 5:
        population3 = evaluateDonaldPopulation(population3);
        break;
    };
  }

  free(population);
  free(population2);
  free(population3);
  return 0;
}

// Arguments: n experiments, pop size, n generations, tour size, cross tax, mut tax
int main(int argc, char* argv[]) {
  int counter = 0;
  time_t t;
  srand(time(&t));
  int problem = argv[1], popsize = argv[2], generations = argv[3];
  int tour = argv[4], cross = argv[5], mutation = argv[6];

  for(int i=0; i<atoi(argv[1]); i++)
    counter += makeExperiment( \
      atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), \
      atoi(argv[5]), atof(argv[6]), atof(argv[7]));
  printf("%d\n", counter);

  return 0;
}
