#ifndef DISCRETE_GENERATOR_H
#define DISCRETE_GENERATOR_H

#include <random>

class DiscreteGenerator{

  public:

    explicit DiscreteGenerator();

    float Generate();

  private:

    std::random_device randomDevice;
    std::mt19937 randomGenerator;
    std::uniform_int_distribution<> discreteDistribution;

};

#endif