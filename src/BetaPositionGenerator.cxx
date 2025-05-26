#include <random>

#include "BetaPositionGenerator.hh"
#include "DiscreteGenerator.hh"

BetaPositionGenerator::BetaPositionGenerator()
  : generator(0, 2) {}

float BetaPositionGenerator::Generate(){

  int randomInt = generator.Generate();

  switch (randomInt){
    case 0: return -1;
    case 1: return 0;
    case 2: return 1;
  }
  return 0; // As a failsafe

}




