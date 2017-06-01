#include "functions.c"
#include "evaluationFunctions.c"
#include "selectionFunctions.c"
#include "crossoverFunctions.c"
#include "mutationFunctions.c"

void makeExperiment(int nexperiments, int ngenerations, int popsize, int tour, int cross, int mutation) {
  Population *population;
  Population *children;
  population = (Population*) malloc(sizeof(Population));
  children = (Population*) malloc(sizeof(Population));
  int found = 0;

  for(int i=0; i<nexperiments; i++) {
    population = initPopulation(population, popsize);
    population = evaluateSendPopulation(population);
    population = sortPopulation(population);

    for(int j=0; j<ngenerations; j++) {
      if (population->individuals[j].evaluation == 0 && found == 0) {
          found = 1;
          for(int k=0; k<10; k++) {
            printf("%d ", population->individuals[j].pvector[k]);
          }
          printf("\n");
      }
      population = tournament(population, 3, 80);
      population = cyclicCrossover(population, 80);
      population = mutate(population, 20);
      population = evaluateSendPopulation(population);
      population = sortPopulation(population);
    }
  }
}

int main() {
  makeExperiment(10, 200, 100, 3, 80, 20);

  return 0;
}
