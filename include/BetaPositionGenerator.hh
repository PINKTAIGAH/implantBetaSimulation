#ifndef BETA_POSITION_GENERATOR_H
#define BETA_POSITION_GENERATOR_H

#include <random>

#include "DiscreteGenerator.hh"

class BetaPositionGenerator{

  public:

    BetaPositionGenerator();

    float Generate();

  private:

    DiscreteGenerator generator;

};

#endif