#include "ConfigReader.hh"
#include <iostream>

// ####### CONSTRUCTOR #######

ConfigReader::ConfigReader(){}

// ####### PRIVATE #######

void ConfigReader::SetDssdSegmentation(const TEnv& env){
  int xSegmentation = env.GetValue("McSim.xSegmentation", 1);
  int ySegmentation = env.GetValue("McSim.ySegmentation", 1);
  dssdSegmentation = std::make_pair(xSegmentation, ySegmentation);
}

void ConfigReader::SetImplantationRate(const TEnv& env){
  implantationRate = env.GetValue("McSim.implantationRate", 0.1);
}

void ConfigReader::SetDecayHalflife(const TEnv& env){
  implantationRate = env.GetValue("McSim.decayHalflife", 0.1);
}

void ConfigReader::SetOnspillPeriod(const TEnv& env){
  onspillPeriod = env.GetValue("McSim.onspillPeriod", 1.);
}

void ConfigReader::SetOffspillPeriod(const TEnv& env){
  offspillPeriod = env.GetValue("McSim.offspillPeriod", 1.);
}

// ####### PUBLIC #######

void ConfigReader::LoadConfig(const std::string configFile){

  // Initialise a TEnv object and check if config file was read correctly
  TEnv env; 
  int status = env.ReadFile(configFile.c_str(), kEnvUser);
  if (status!=0) std::cerr << "[WARNING] Problem reading config file: " << configFile << std::endl;

  // Read and assign each parameter
  SetDssdSegmentation(env);
  SetImplantationRate(env);
  SetDecayHalflife(env);
  SetOnspillPeriod(env);
  SetOffspillPeriod(env);

}

std::pair<int, int> ConfigReader::GetDssdSegmentation() const {
  return dssdSegmentation;
}

float ConfigReader::GetImplantationRate() const {
  return implantationRate;
}

float ConfigReader::GetDecayHalflife() const {
  return decayHalflife;
}

float ConfigReader::GetOnspillPeriod() const {
  return onspillPeriod;
}

float ConfigReader::GetOffspillPeriod() const {
  return offspillPeriod;
}
