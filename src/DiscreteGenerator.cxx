#include <random>

#include "DiscreteGenerator.hh"

DiscreteGenerator::DiscreteGenerator() 
    : randomDevice(), randomGenerator(randomDevice()), discreteDistribution(0, 2) {}

float DiscreteGenerator::Generate(){

  int randomInt = discreteDistribution(randomGenerator);

  switch (randomInt){
    case 0: return -1;
    case 1: return 0;
    case 2: return 1;
  }
  return 0; // As a failsafe

}




