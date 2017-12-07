#include "types.h"

Individual mutate(Individual individual, double rate) {
  double randDouble, baseWeight;
  int i, randInt;

  for(i=0; i<INDIVIDUALSIZE; i++) {
    randDouble = (double)rand()/(double)RAND_MAX;
    // Weight mutation
    if(randDouble <= rate) {
      randDouble = (double)rand()/(double)RAND_MAX;
      // Transform to a number less then 1/3
      randDouble = randDouble / 3.0;
      // Verify operation to maintain number in [0..1]
      baseWeight = individual.cromossome[i].weight;
      if(randDouble > baseWeight)
        individual.cromossome[i].weight = randDouble - baseWeight;
      else
        individual.cromossome[i].weight = randDouble + baseWeight;
    }

    randDouble = (double)rand()/(double)RAND_MAX;
    // Operator mutation
    if(randDouble <= rate) {
      // Change operator for continuous variable
      if(individual.cromossome[i].continuous == 1) {
        randInt = rand() % 2;
        individual.cromossome[i].op = randInt;
      }
      // Change operator for nominal variable
      else {
        randInt = rand() % 2 + 2;
        individual.cromossome[i].op = randInt;
      }
    }

    randDouble = (double)rand()/(double)RAND_MAX;
    // Value mutation
    if(randDouble <= rate) {
      if(individual.cromossome[i].continuous == 1) {
        randInt = rand() % 4;
        individual.cromossome[i].value = randInt;
      }
      // Family history
      else if(i==12) {
        randInt = rand() % 2;
        individual.cromossome[i].value = randInt;
      }
    }
  }

  return individual;
}
