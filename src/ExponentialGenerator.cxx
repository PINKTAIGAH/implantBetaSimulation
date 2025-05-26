#include <random>

#include "ExponentialGenerator.hh"

ExponentialGenerator::ExponentialGenerator(float lambda) 
    : randomGenerator(std::random_device{}()), exponentialDistribution(lambda) {}


void ExponentialGenerator::SetLambda(float lambda){

  exponentialDistribution.param(std::exponential_distribution<>::param_type(lambda));

}

float ExponentialGenerator::Generate(){
  return exponentialDistribution(randomGenerator);
}
