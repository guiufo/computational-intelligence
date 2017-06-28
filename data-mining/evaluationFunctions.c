#include "types.h"
#include "helperFunctions.h"

Individual* fitness(Individual* individual, int** data, int diseaseClass) {
  int i, j;
  // Train individual
  for(i=0; i<238; i++){

    if(data[i][34] == diseaseClass){
      for(j=0; j<34; j++) {
          switch individual.cromossome[j].op {
            case 0:
              if(individual.cromossome[j].value >= data[i][j]) {

              }
          }
      }
    }
  }

}

int match(int value, Base base) {
    int matched = 0;

    switch(base.op){
        case 0:
          if()
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
    }

    return matched;
}
