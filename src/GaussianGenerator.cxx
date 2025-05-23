#include <random>

#include "GaussianGenerator.hh"

GaussianGenerator::GaussianGenerator(float mean, float stdError) 
    : randomGenerator(std::random_device{}()), gaussianDistribution(mean, stdError) {}


void GaussianGenerator::SetParameters(float mean, float stdError){

  gaussianDistribution.param(std::normal_distribution<>::param_type(mean, stdError));

}

float GaussianGenerator::Generate(){
  return gaussianDistribution(randomGenerator);
}




