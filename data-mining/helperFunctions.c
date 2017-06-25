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
      population->individuals[i].cromossome[j][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[j][1] = rand() % 2;
      population->individuals[i].cromossome[j][2] = rand() % 4;
      population->individuals[i].continuous = 1;
    }
      // age from 0 to 100
      population->individuals[i].cromossome[32][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[32][1] = rand() % 2 + 2;
      population->individuals[i].cromossome[32][2] = rand() % 100;
      population->individuals[i].continuous = 1;

      // family history
      population->individuals[i].cromossome[33][0] = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[33][1] = rand() % 2 + 2;
      population->individuals[i].cromossome[33][2] = rand() % 2;
      population->individuals[i].continuous = 1;
  }
  return population;
}

// Show population
void showPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < 34; j++) {
      printf("%.2f %.0f %.0f|", population->individuals[i].cromossome[j][0],
      population->individuals[i].cromossome[j][1], population->individuals[i].cromossome[j][2]);
    }
    printf("\n");
    printf("\n");
  }
}

int** getDermatologyData() {
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
