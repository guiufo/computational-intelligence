/*
 * types.h
 * Copyright (C) 2017 guiufo <guiufo@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef TYPES_H
#define TYPES_H

// Big integer
#define BIGINT 10000000
#define THRESHOLD 0.3
#define TRAININGSIZE 238
#define TESTSIZE 120
#define INDIVIDUALSIZE 33

typedef struct base {
  float weight;
  // Operator mapping: 0 -> >=, 1 -> <, 2 -> =, 3 -> !=
  int op;
  int value;
  int continuous;
  int present;
}Base;

// Type to hold training and testing data
typedef struct data {
  int **training;
  int **testing;
} Data;

// Age is not included
typedef struct individual {
  Base cromossome[33];
	float fitness;
}Individual;

typedef struct population {
	Individual *individuals;
	int psize;
}Population;

#endif /* !TYPES_H */
