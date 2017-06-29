#include "types.h"

Individual* mutation(Individual* individual, float rate) {
  float randFloat;
  int i, randInt;

  for(i=0; i<INDIVIDUALSIZE; i++) {
    randFloat = (double)rand()/(double)RAND_MAX;
    // Weight mutation
    if(randFloat <= rate) {
      randFloat = (double)rand()/(double)RAND_MAX;
      randFloat = randFloat / 3;
      if(randFloat > individual.cromossome[i].weight)
        individual.cromossome[i].weight += randFloat;
      else
        individual.cromossome[i].weight -= randFloat;
    }

    randFloat = (double)rand()/(double)RAND_MAX;
    // Operator mutation
    if(randFloat <= rate) {
      if(individual.cromossome[i].continuous == 1) {
        randInt = rand() % 2;
        individual.cromossome[i].op = randInt;
      }
      else {
        randInt = rand() % 2 + 2;
        individual.cromossome[i].op = randInt;
      }
    }

    randFloat = (double)rand()/(double)RAND_MAX;
    // Value mutation
    if(randFloat <= rate) {
      if(individual.cromossome[i].continuous == 1) {
        randInt = rand() % 4;
        individual.cromossome[i].value = randInt;
      }
      // Family history
      else if(i==12) {
        randInt = rand() % 2;
        individual.cromossome[i].value = randInt;
      }
      // Age
      else if(i==33) {
        randInt = rand() % 100;
        individual.cromossome[i].value = randInt;
      }
    }
  }

  return individual;
}
