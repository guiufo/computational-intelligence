#include "functions.h"

Population* evaluateSendPopulation(Population *population);
Individual evaluateSendIndividual(Individual individual);

Population* evaluateEatPopulation(Population *population);
Individual evaluateEatIndividual(Individual);

Population* evaluateSendPopulation(Population *population) {
  for(int i = 0; i < population->populationSize; i++){
    population->individuals[i] = evaluateSendIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateSendIndividual(Individual individual) {
  int send, more, money;
  send = more = money = 0;
	send = individual.pvector[0]*1000+individual.pvector[1]*100 \
    +individual.pvector[2]*10+individual.pvector[3];
	more = individual.pvector[4]*1000+individual.pvector[5]*100 \
    +individual.pvector[6]*10+individual.pvector[1];
	money = individual.pvector[4]*10000+individual.pvector[5]*1000 \
    +individual.pvector[2]*100+individual.pvector[1]*10+individual.pvector[7];
	// Set evaluation value for the i'th individual
	individual.evaluation = abs((send + more) - money);
  return individual;
}

Population* evaluateEatPopulation(Population *population) {
  for(int i = 0; i < population->populationSize; i++){
    population->individuals[i] = evaluateEatIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateEatIndividual(Individual individual) {
  int eat, that, apple;
  eat = that = apple = 0;
	eat = individual.pvector[0]*100+individual.pvector[1]*10 \
    +individual.pvector[2]*10;
	that = individual.pvector[2]*1000+individual.pvector[3]*100 \
    +individual.pvector[1]*10+individual.pvector[2];
	apple = individual.pvector[1]*10000+individual.pvector[4]*1000 \
    +individual.pvector[4]*100+individual.pvector[5]*10+individual.pvector[0];
	// Set evaluation value for the i'th individual
	individual.evaluation = abs((eat + that) - apple);
  return individual;
}
