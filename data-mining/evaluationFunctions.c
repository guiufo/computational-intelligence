#include "types.h"

int match(Individual individual, int* dataRow);
Individual fitness(Individual individual, int** data, int diseaseClass);

Individual fitness(Individual individual, int** data, int diseaseClass) {
  int i, matched;
  // True positive, False positive, True negative and False negative
  double tp, fp, tn, fn, se, sp;
  tp = fp = tn = fn = 0;

  // Train individual
  for(i=0; i<TESTINDEX; i++) {
    matched = match(individual, data[i]);
    if(matched && data[i][CLASSINDEX] == diseaseClass)
      tp += 1;
    if(matched && data[i][CLASSINDEX] != diseaseClass)
      fp += 1;
    if(!matched && data[i][CLASSINDEX] != diseaseClass)
      tn += 1;
    if(!matched && data[i][CLASSINDEX] == diseaseClass)
      fn += 1;
  }

  se = tp/(tp+fn);
  sp = tn/(tn+fp);
  // Return individual fitness
  // individual.fitness = se * sp;
  individual.fitness = se * sp;

  return individual;
}


// Return 1 if individual match a data row
int match(Individual individual, int* dataRow) {
  int i, matched;

  for(i=0; i<INDIVIDUALSIZE; i++){
    // Verify if rule is present
    if(individual.cromossome[i].weight < THRESHOLD) {
      if(dataRow[i] == 0)
        matched = 1;
      else matched = 0;
    }
    // If rule is present
    else if(individual.cromossome[i].weight >= THRESHOLD) {
      // op == 0 ----> >=
      if(individual.cromossome[i].op == 0) {
        if(individual.cromossome[i].value >= dataRow[i])
          matched = 1;
        else matched = 0;
      }
      // op == 1 ----> <
      else if(individual.cromossome[i].op == 1) {
        if(individual.cromossome[i].value < dataRow[i])
          matched = 1;
        else matched = 0;
      }
      // op == 2 ----> ==
      else if(individual.cromossome[i].op == 2) {
        if(individual.cromossome[i].value == dataRow[i])
          matched = 1;
        else matched = 0;
      }
      // op == 3 ----> !=
      else if(individual.cromossome[i].op == 3) {
        if(!(individual.cromossome[i].value != dataRow[i]))
          matched = 1;
        else matched = 0;
      }
    }

  }

  return matched;
}
