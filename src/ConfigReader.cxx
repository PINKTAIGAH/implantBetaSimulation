#include "ConfigReader.hh"
#include <iostream>

// ####### CONSTRUCTOR #######

ConfigReader::ConfigReader(){}

// ####### PRIVATE #######

// Setters

void ConfigReader::SetDssdSegmentation(const TEnv& env){
  int xSegmentation = env.GetValue("MCSim.xSegmentation", 1);
  int ySegmentation = env.GetValue("MCSim.ySegmentation", 1);
  dssdSegmentation = std::make_pair(xSegmentation, ySegmentation);
}

void ConfigReader::SetImplantationPositionCharacteristics(const TEnv& env){
  float implantCentroidX = env.GetValue("MCSim.implantCentroidX", 1.);
  float implantCentroidY = env.GetValue("MCSim.implantCentroidY", 1.);
  float implantStdErrorX = env.GetValue("MCSim.implantStdErrorX", 0.);
  float implantStdErrorY = env.GetValue("MCSim.implantStdErrorY", 0.);
  implantationPositionCharacteristics = {implantCentroidX, implantCentroidY, implantStdErrorX, implantStdErrorY};
}

void ConfigReader::SetDecayNearestNeighbours(const TEnv& env){
  decayNearestNeighbours = env.GetValue("MCSim.decayNearestNeighbours", 1);
}

void ConfigReader::SetImplantationRate(const TEnv& env){
  implantationRate = env.GetValue("MCSim.implantationRate", 0.1);
}

void ConfigReader::SetDecayHalflife(const TEnv& env){
  decayHalflife = env.GetValue("MCSim.decayHalflife", 0.1);
}

void ConfigReader::SetBetaEfficiency(const TEnv& env){
  betaEfficiency = env.GetValue("MCSim.betaEfficiency", 1.);
}

void ConfigReader::SetOnspillPeriod(const TEnv& env){
  onspillPeriod = env.GetValue("MCSim.onspillPeriod", 1.);
}

void ConfigReader::SetOffspillPeriod(const TEnv& env){
  offspillPeriod = env.GetValue("MCSim.offspillPeriod", 1.);
}

void ConfigReader::SetStartTime(const TEnv& env){
  startTime = env.GetValue("MCSim.startTime", 0.);
}

void ConfigReader::SetEndTime(const TEnv& env){
  endTime = env.GetValue("MCSim.endTime", 100.);
}

void ConfigReader::SetTimestep(const TEnv& env){
  timestep = env.GetValue("MCSim.timestep", 1e-1);
}

void ConfigReader::SetCorrelationWindow(const TEnv& env){
  correlationWindow = env.GetValue("MCSim.correlationWindow", 1.);
}

void ConfigReader::SetDebug(const TEnv& env){
  debug = env.GetValue("Backend.debug", false);
}

// ####### PUBLIC #######

void ConfigReader::LoadConfig(const std::string configFile){

  // Initialise a TEnv object and check if config file was read correctly
  TEnv env; 
  int status = env.ReadFile(configFile.c_str(), kEnvUser);
  if (status!=0) std::cerr << "[WARNING] Problem reading config file: " << configFile << std::endl;

  // Read and assign each parameter
  SetDssdSegmentation(env);
  SetImplantationPositionCharacteristics(env);
  SetDecayNearestNeighbours(env);
  SetImplantationRate(env);
  SetDecayHalflife(env);
  SetBetaEfficiency(env);
  SetOnspillPeriod(env);
  SetOffspillPeriod(env);
  SetStartTime(env);
  SetEndTime(env);
  SetTimestep(env);
  SetCorrelationWindow(env);
  SetDebug(env);

}

// Getters

std::pair<int, int> ConfigReader::GetDssdSegmentation() const {
  return dssdSegmentation;
}

std::array<float, 4> ConfigReader::GetImplantationPositionCharacteristics() const {
  return implantationPositionCharacteristics;
}

int ConfigReader::GetDecayNearestNeighbours() const {
  return decayNearestNeighbours;
}

float ConfigReader::GetImplantationRate() const {
  return implantationRate;
}

float ConfigReader::GetDecayHalflife() const {
  return decayHalflife;
}

float ConfigReader::GetBetaEfficiency() const {
  return betaEfficiency;
}

float ConfigReader::GetOnspillPeriod() const {
  return onspillPeriod;
}

float ConfigReader::GetOffspillPeriod() const {
  return offspillPeriod;
}

float ConfigReader::GetStartTime() const {
  return startTime; 
}

float ConfigReader::GetEndTime() const {
  return endTime; 
}

float ConfigReader::GetTimestep() const {
  return timestep; 
}

float ConfigReader::GetCorrelationWindow() const {
  return correlationWindow; 
}

bool ConfigReader::GetDebug() const {
  return debug; 
}