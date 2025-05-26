#include <random>

#include "UniformGenerator.hh"

UniformGenerator::UniformGenerator(float upperBound, float lowerBound) 
    : randomGenerator(std::random_device{}()), uniformDistribution(lowerBound, upperBound) {}


void UniformGenerator::SetRange(float lowerBound, float upperBound){

  uniformDistribution.param(std::uniform_real_distribution<>::param_type(lowerBound,upperBound));

}

float UniformGenerator::Generate(){
  return uniformDistribution(randomGenerator);
}