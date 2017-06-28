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

typedef struct base {
  float weight;
  // Operator mapping: 0 -> >=, 1 -> <, 2 -> =, 3 -> !=
  int op;
  int value;
  int continuous;
  int present;
}Base;

typedef struct individual {
  Base cromossome[34];
	float fitness;
}Individual;

typedef struct population {
	Individual *individuals;
	int psize;
}Population;

#endif /* !TYPES_H */
