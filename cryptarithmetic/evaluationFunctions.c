#include "types.h"

Population* evaluateSendPopulation(Population *population);
Individual evaluateSendIndividual(Individual individual);

Population* evaluateEatPopulation(Population *population);
Individual evaluateEatIndividual(Individual individual);

Population* evaluateSendPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateSendIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateSendIndividual(Individual individual) {
  int send, more, money;
  send = more = money = 0;
	send = individual.dna[0]*1000+individual.dna[1]*100 \
    +individual.dna[2]*10+individual.dna[3];
	more = individual.dna[4]*1000+individual.dna[5]*100 \
    +individual.dna[6]*10+individual.dna[1];
	money = individual.dna[4]*10000+individual.dna[5]*1000 \
    +individual.dna[2]*100+individual.dna[1]*10+individual.dna[7];
	// Set fitness value for the i'th individual
	individual.fitness = abs((send + more) - money);
  return individual;
}

Population* evaluateEatPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateEatIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateEatIndividual(Individual individual) {
  int eat, that, apple;
  eat = that = apple = 0;
	eat = individual.dna[0]*100+individual.dna[1]*10 \
    +individual.dna[2]*10;
	that = individual.dna[2]*1000+individual.dna[3]*100 \
    +individual.dna[1]*10+individual.dna[2];
	apple = individual.dna[1]*10000+individual.dna[4]*1000 \
    +individual.dna[4]*100+individual.dna[5]*10+individual.dna[0];
	// Set fitness value for the i'th individual
	individual.fitness = abs((eat + that) - apple);
  return individual;
}
