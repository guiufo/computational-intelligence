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
#define INDIVIDUAL_SIZE 34

// Individual is a "hard" type
typedef struct individual {
  // Each gene has weight, operator and value
  // Operator mapping: 0 -> >=, 1 -> <, 2 -> =, 3 -> !=
  float cromossome[34][3];
	int fitness;
  int nominal;
}Individual;

#define INDIVIDUAL_SIZE 34
// Population is a "dynamic" type
typedef struct population {
	Individual *individuals;
	int psize;
}Population;

#endif /* !TYPES_H */
