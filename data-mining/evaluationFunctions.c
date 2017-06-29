#include "types.h"

Individual fitness(Individual individual, int** data, int dclass) {
  int i, matched;
  // True positive, False positive, True negative and False negative
  float tp, fp, tn, fn, se, sp;
  tp = fp = tn = fn = 0;

  // Train individual
  for(i=0; i<TESTSIZE; i++) {
    matched = match(individual, data[i]);
    if(matched && data[i][INDIVIDUALSIZE] == dclass)
      tp += 1;
    else if(matched && data[i][INDIVIDUALSIZE] != dclass)
      fp += 1;
    else if(!matched && data[i][INDIVIDUALSIZE] != dclass)
      tn += 1;
    if(!matched && data[i][INDIVIDUALSIZE] == dclass)
      fn += 1;
  }

  se = tp/(tp+fn);
  sp = tn/(tn+fp);
  // Return individual fitness
  individual.fitness = se * sp;

  return individual;
}


// Return 1 if individual match a data row
int match(Individual individual, int* dataRow) {
  int i, matched;

  for(i=0; i<INDIVIDUALSIZE; i++){
    // Verify if rule is present
    if(individual.cromossome[i].weight < THRESHOLD) {
      if(dataRow[i] != 0) {
        return 0;
      }
    }
    else if(individual.cromossome[i].weight >= THRESHOLD) {
      if(individual.cromossome[i].continuous) {
        // op == 0 ----> >=
        if(individual.cromossome[i].op == 0) {
          if(!(individual.cromossome[i].value >= dataRow[i]))
            return 0;
        }
        // op == 1 ----> <
        else if(individual.cromossome[i].op == 1) {
          if(!(individual.cromossome[i].value < dataRow[i]))
            return 0;
        }
      }
      else {
        // op == 2 ----> ==
        if(individual.cromossome[i].op == 2) {
          if(!(individual.cromossome[i].value == dataRow[i]))
            return 0;
        }
        // op == 3 ----> !=
        else if(individual.cromossome[i].op == 3) {
          if(!(individual.cromossome[i].value != dataRow[i]))
            return 0;
        }
      }
    }

  }

  return 1;
}
