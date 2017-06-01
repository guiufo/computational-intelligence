/*
 * functions.h
 * Copyright (C) 2017 guiufo <guiufo@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

typedef struct individual {
	// permutation vector
  int pvector[10];
	int evaluation;
}Individual;

typedef struct population {
	Individual *individuals;
	int populationSize;
	int problemSize;
}Population;

#endif /* !FUNCTIONS_H */
