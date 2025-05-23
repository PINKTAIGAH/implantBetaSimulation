#ifndef GAUSSIAN_GENERATOR_H
#define GAUSSIAN_GENERATOR_H

#include <random>

class GaussianGenerator{

  public:

    explicit GaussianGenerator(float mean=1., float stdError=0.);

    void SetParameters(float mean, float stdError );

    float Generate();

  private:

    std::mt19937 randomGenerator;
    std::normal_distribution<> gaussianDistribution;

};

#endif