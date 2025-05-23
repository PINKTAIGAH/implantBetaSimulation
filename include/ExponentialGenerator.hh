#ifndef EXPONENTIAL_GENERATOR_H
#define EXPONENTIAL_GENERATOR_H

#include <random>

class ExponentialGenerator{

  public:

    explicit ExponentialGenerator(float lambda=1.);

    void SetLambda(float lambda);

    float Generate();

  private:

    std::mt19937 randomGenerator;
    std::exponential_distribution<> exponentialDistribution;

};

#endif