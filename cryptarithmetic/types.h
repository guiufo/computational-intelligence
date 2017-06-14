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

// Individual is a "hard" type
typedef struct individual {
  int cromossome[10];
	int fitness;
}Individual;

// Population is a "dynamic" type
typedef struct population {
	Individual *individuals;
	int psize;
}Population;

#endif /* !TYPES_H */
