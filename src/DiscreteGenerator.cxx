#include <random>

#include "DiscreteGenerator.hh"


DiscreteGenerator::DiscreteGenerator(int lowerBound, int upperBound) 
    : randomGenerator(std::random_device{}()), discreteDistribution(lowerBound, upperBound) {}


void DiscreteGenerator::SetRange(int lowerBound, int upperBound){

  discreteDistribution.param(std::uniform_int_distribution<>::param_type(lowerBound,upperBound));

}

int DiscreteGenerator::Generate(){
  return discreteDistribution(randomGenerator);
}