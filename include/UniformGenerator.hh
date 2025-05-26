#ifndef UNIFORM_GENERATOR_H
#define UNIFORM_GENERATOR_H

#include <random>

class UniformGenerator{

  public:

    explicit UniformGenerator(float lowerBound=0., float upperBound=1.);

    void SetRange(float lowerBound, float upperBound );

    float Generate();

  private:

    std::mt19937 randomGenerator;
    std::uniform_real_distribution<> uniformDistribution;

};

#endif