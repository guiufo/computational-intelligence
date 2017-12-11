#include "types.h"

Population* evaluateSendPopulation(Population *population);
Individual evaluateSendIndividual(Individual individual);

Population* evaluateEatPopulation(Population *population);
Individual evaluateEatIndividual(Individual individual);

Population* evaluateCrossPopulation(Population *population);
Individual evaluateCrossIndividual(Individual individual);

Population* evaluateCocaPopulation(Population *population);
Individual evaluateCocaIndividual(Individual individual);

Population* evaluateDonaldPopulation(Population *population);
Individual evaluateDonaldIndividual(Individual individual);

Population* evaluateSendPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateSendIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateSendIndividual(Individual individual) {
  // 01234567
  // sendmory
  int send, more, money;
  send = more = money = 0;
	send = individual.cromossome[0]*1000+individual.cromossome[1]*100 \
    +individual.cromossome[2]*10+individual.cromossome[3];
	more = individual.cromossome[4]*1000+individual.cromossome[5]*100 \
    +individual.cromossome[6]*10+individual.cromossome[1];
	money = individual.cromossome[4]*10000+individual.cromossome[5]*1000 \
    +individual.cromossome[2]*100+individual.cromossome[1]*10+individual.cromossome[7];
	// Set fitness value for the i'th individual
	individual.fitness = abs(send + more - money);
  return individual;
}

Population* evaluateEatPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateEatIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateEatIndividual(Individual individual) {
  // 012345
  // eathpl
  int eat, that, apple;
  eat = that = apple = 0;
	eat = individual.cromossome[0]*100+individual.cromossome[1]*10 \
    +individual.cromossome[2];
	that = individual.cromossome[2]*1000+individual.cromossome[3]*100 \
    +individual.cromossome[1]*10+individual.cromossome[2];
	apple = individual.cromossome[1]*10000+individual.cromossome[4]*1000 \
    +individual.cromossome[4]*100+individual.cromossome[5]*10+individual.cromossome[0];
	// Set fitness value for the i'th individual
	individual.fitness = abs(eat + that - apple);
  return individual;
}

Population* evaluateCrossPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateCrossIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateCrossIndividual(Individual individual) {
  // 012345678
  // crosadnge
  int cross, roads, danger;
  cross = roads = danger = 0;
	cross = individual.cromossome[0]*10000+individual.cromossome[1]*1000 \
    +individual.cromossome[2]*100+individual.cromossome[3]*10+individual.cromossome[3];
	roads = individual.cromossome[1]*10000+individual.cromossome[2]*1000 \
    +individual.cromossome[4]*100+individual.cromossome[5]*10+individual.cromossome[3];
	danger = individual.cromossome[5]*100000+individual.cromossome[4]*10000 \
    +individual.cromossome[6]*1000+individual.cromossome[7]*100+individual.cromossome[8]*10+individual.cromossome[1];
	// Set fitness value for the i'th individual
	individual.fitness = abs(cross + roads - danger);
  return individual;
}

Population* evaluateCocaPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateCocaIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateCocaIndividual(Individual individual) {
  // 012345
  // coalsi
  int coca, cola, oasis;
  coca = cola = oasis = 0;
	coca = individual.cromossome[0]*1000+individual.cromossome[1]*100 \
    +individual.cromossome[0]*10+individual.cromossome[2];
	cola = individual.cromossome[0]*1000+individual.cromossome[1]*100 \
    +individual.cromossome[3]*10+individual.cromossome[2];
	oasis = individual.cromossome[1]*10000+individual.cromossome[2]*1000 \
    +individual.cromossome[4]*100+individual.cromossome[5]*10+individual.cromossome[4];
	// Set fitness value for the i'th individual
	individual.fitness = abs(coca + cola - oasis);
  return individual;
}

Population* evaluateDonaldPopulation(Population *population) {
  for(int i = 0; i < population->psize; i++){
    population->individuals[i] = evaluateDonaldIndividual(population->individuals[i]);
  }
  return population;
}

Individual evaluateDonaldIndividual(Individual individual) {
  // 0123456789
  // donalgerbt
  int donald, gerald, robert;
  donald = gerald = robert = 0;
	donald = individual.cromossome[0]*100000+individual.cromossome[1]*10000 \
    +individual.cromossome[2]*1000+individual.cromossome[3]*100+individual.cromossome[4]*10+individual.cromossome[0];
	gerald = individual.cromossome[5]*100000+individual.cromossome[6]*10000 \
    +individual.cromossome[7]*1000+individual.cromossome[3]*100+individual.cromossome[4]*10+individual.cromossome[0];
	robert = individual.cromossome[7]*100000+individual.cromossome[1]*10000 \
    +individual.cromossome[8]*1000+individual.cromossome[6]*100+individual.cromossome[7]*10+individual.cromossome[9];
	// Set fitness value for the i'th individual
	individual.fitness = abs(donald + gerald - robert);
  return individual;
}
