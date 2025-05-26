#ifndef DISCRETE_GENERATOR_H
#define DISCRETE_GENERATOR_H

#include <random>

class DiscreteGenerator{

  public:

    explicit DiscreteGenerator(int lowerBound=0, int upperBound=1);

    void SetRange(int lowerBound, int upperBound );

    int Generate();

  private:

    std::mt19937 randomGenerator;
    std::uniform_int_distribution<> discreteDistribution;

};

#endif