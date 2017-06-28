#include "types.h"

// Functions signatures
Population* initPopulation(Population *population, int psize);
void showPopulation(Population *population);
void showDermatologyData(int** data);
int** getDermatologyData();

// Init a random population of given size
Population* initPopulation(Population *population, int psize) {
  int i, j, temp, tempRand;
  population = (Population*) malloc(sizeof(Population));

  population->psize = psize;
  population->individuals = malloc(psize * sizeof(Individual));
  for(i=0; i < psize; i++){
    for(j=0;j<32;j++){
      population->individuals[i].cromossome[j].weight = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[j].op = rand() % 2;
      population->individuals[i].cromossome[j].value = rand() % 4;
      population->individuals[i].cromossome[j].continuous = 1;
      population->individuals[i].cromossome[j].present = 0;
    }
      // family history is 0 or 1
      population->individuals[i].cromossome[32].weight = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[32].op = rand() % 2 + 2;
      population->individuals[i].cromossome[32].value = rand() % 2;
      population->individuals[i].cromossome[32].continuous = 0;
      population->individuals[i].cromossome[32].present = 0;

      // age from 0 to 100
      population->individuals[i].cromossome[33].weight = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[33].op = rand() % 2 + 2;
      population->individuals[i].cromossome[33].value = rand() % 100;
      population->individuals[i].cromossome[33].continuous = 0;
      population->individuals[i].cromossome[33].present = 0;
  }
  return population;
}

// Show population
void showPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < 34; j++) {
      printf("%.2f %d %d|", population->individuals[i].cromossome[j].weight,
      population->individuals[i].cromossome[j].op, population->individuals[i].cromossome[j].value);
    }
    printf("\n");
    printf("\n");
  }
}


int** getTrainingData() {
    int** matrix;
    int i, j;
    matrix = (int**)malloc(358 * sizeof(int*));
    for(i=0; i<358; i++)
        matrix[i] = (int*)malloc(35 * sizeof(int));

    FILE *fp;
    int data,row,col,c,count,inc;
    int *array, capacity=35;
    char ch;
    array=(int*)malloc(sizeof(int)*capacity);
    fp=fopen("data/dermatology.data","r");
    row=col=c=count=0;
    while(EOF!=(inc=fscanf(fp,"%d%c", &data, &ch)) && inc == 2){
        ++c;//COLUMN count
        if(capacity==count)
            array=(int*)realloc(array, sizeof(int)*(capacity*=2));
        array[count++] = data;
        if(ch == '\n'){
            ++row;
            if(col == 0){
                col = c;
            } else if(col != c){
                fprintf(stderr, "format error of different Column of Row at %d\n", row);
                goto exit;
            }
            c = 0;
        } else if(ch != ','){
            fprintf(stderr, "format error of different separator(%c) of Row at %d \n", ch, row);
            goto exit;
        }
    }

    for(i=0;i<row;++i){
        for(j=0;j<col;++j)
            matrix[i][j] = array[i*col + j];
    }

exit:
    fclose(fp);
    return matrix;
}

void showDermatologyData(int** data) {
  int i, j;
  for(i=0; i<358; i++){
    for(j=0; j<35; j++) {
      printf("%d,", data[i][j]);
    }
    printf("\n");
  }
}
