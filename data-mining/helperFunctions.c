#include "types.h"

// Functions signatures
Population* initPopulation(Population *population, int psize);
void showPopulation(Population *population);
void showData(int** data);
Data* getData(int diseaseClass);
Population* sortPopulation(Population* population);

// Init a random population of given size
Population* initPopulation(Population *population, int psize) {
  int i, j, temp, tempRand;
  population = (Population*) malloc(sizeof(Population));

  population->psize = psize;
  population->individuals = malloc(psize * sizeof(Individual));
  for(i=0; i < psize; i++){
    for(j=0;j<33;j++){
      population->individuals[i].cromossome[j].weight = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[j].op = rand() % 2;
      population->individuals[i].cromossome[j].value = rand() % 4;
      population->individuals[i].cromossome[j].continuous = 1;
      population->individuals[i].cromossome[j].present = 0;
    }
      // family history is 0 or 1
      population->individuals[i].cromossome[12].weight = (double)rand()/(double)RAND_MAX;
      population->individuals[i].cromossome[12].op = rand() % 2 + 2;
      population->individuals[i].cromossome[12].value = rand() % 2;
      population->individuals[i].cromossome[12].continuous = 0;
      population->individuals[i].cromossome[12].present = 0;
  }
  return population;
}

// Show full population
void showFullPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < INDIVIDUALSIZE; j++) {
      printf("%.2f %d %d|", population->individuals[i].cromossome[j].weight,
      population->individuals[i].cromossome[j].op, population->individuals[i].cromossome[j].value);
    }
    printf("\n");
    printf("\n");
  }
}

// Show population (Resumed individual)
void showPopulation(Population *population) {
  int i, j;
  printf("\n");
  for(i = 0; i < population->psize; i++){
    for(j = 0; j < 5; j++) {
      printf("%.2f %d %d|", population->individuals[i].cromossome[j].weight,
      population->individuals[i].cromossome[j].op, population->individuals[i].cromossome[j].value);
    }
    printf("  ...  ");
    for(j = 29; j < INDIVIDUALSIZE; j++) {
      printf("%.2f %d %d|", population->individuals[i].cromossome[j].weight,
      population->individuals[i].cromossome[j].op, population->individuals[i].cromossome[j].value);
    }
    printf("   %f", population->individuals[i].fitness);
    printf("\n");
    printf("\n");
  }
}

// Reads file with dermatology data an return a matrix of the data
Data* getData(int diseaseClass) {
    int** matrix;
    int i, j;
    Data* ddata;

    // Alloc matrix to hold all data
    matrix = (int**)malloc(358 * sizeof(int*));
    for(i=0; i<358; i++)
        matrix[i] = (int*)malloc(35 * sizeof(int));

    // Alloc Data struct to hold training and test data
    ddata = (Data*) malloc(sizeof(Data));
    ddata->training = malloc(238*sizeof(int*));
    ddata->testing = malloc(120*sizeof(int*));
    for(i=0; i<238; i++)
      ddata->training[i] = malloc(DATAROWSIZE*sizeof(int));
    for(i=0; i<120; i++)
      ddata->testing[i] = malloc(DATAROWSIZE*sizeof(int));

    // Read file
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

    // Generate data struct based on disease class

    // Generate data struct to test
    for(i=0; i<238; i++) {
      for(j=0; j<DATAROWSIZE; j++) {
        ddata->training[i][j] = matrix[i][j];
      }
    }

    for(i=238; i<358; i++) {
      for(j=0; j<DATAROWSIZE; j++) {
        ddata->testing[i-238][j] = matrix[i][j];
      }
    }

exit:
    fclose(fp);
    return ddata;
}

// Show training data
void showTrainingData(Data* data) {
  int i, j;
  for(i=0; i<238; i++){
    for(j=0; j<DATAROWSIZE; j++) {
      printf("%d,", data->training[i][j]);
    }
    printf("\n");
  }
}

// Show training data
void showTestingData(Data* data) {
  int i, j;
  for(i=0; i<120; i++){
    for(j=0; j<DATAROWSIZE; j++) {
      printf("%d,", data->testing[i][j]);
    }
    printf("\n");
  }
}

// Insertion sort in decreasing order
Population* sortPopulation(Population *population) {
  int i, j;
	Individual tempIndividual;
	for(i=1; i < population->psize; i++) {
		j = i;
		while(j>0 && population->individuals[j].fitness > population->individuals[j-1].fitness) {
			tempIndividual = population->individuals[j];
			population->individuals[j] = population->individuals[j-1];
			population->individuals[j-1] = tempIndividual;
			j--;
		}
	}

	return population;
}
