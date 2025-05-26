#include "ConfigReader.hh"
#include <iostream>

// ####### CONSTRUCTOR #######

ConfigReader::ConfigReader(){}

// ####### PRIVATE #######

// Setters

void ConfigReader::SetDssdSegmentation(const TEnv& env){
  int xSegmentation = env.GetValue("Detector.xSegmentation", 1);
  int ySegmentation = env.GetValue("Detector.ySegmentation", 1);
  dssdSegmentation = std::make_pair(xSegmentation, ySegmentation);
}

void ConfigReader::SetBetaEfficiency(const TEnv& env){
  betaEfficiency = env.GetValue("Detector.betaEfficiency", 1.);
}

void ConfigReader::SetNoiseRate(const TEnv& env){
  noiseRate = env.GetValue("Detector.noiseRate", 0.1);
}

void ConfigReader::SetImplantationPositionCharacteristics(const TEnv& env){
  float implantCentroidX = env.GetValue("Implant.centroidX", 1.);
  float implantCentroidY = env.GetValue("Implant.centroidY", 1.);
  float implantStdErrorX = env.GetValue("Implant.stdErrorX", 0.);
  float implantStdErrorY = env.GetValue("Implant.stdErrorY", 0.);
  implantationPositionCharacteristics = {implantCentroidX, implantCentroidY, implantStdErrorX, implantStdErrorY};
}

void ConfigReader::SetImplantationRate(const TEnv& env){
  implantationRate = env.GetValue("Implant.rate", 0.1);
}

void ConfigReader::SetDecayNearestNeighbours(const TEnv& env){
  decayNearestNeighbours = env.GetValue("Decay.nearestNeighbours", 1);
}

void ConfigReader::SetDecayHalflife(const TEnv& env){
  decayHalflife = env.GetValue("Decay.halflife", 0.1);
}

void ConfigReader::SetOnspillPeriod(const TEnv& env){
  onspillPeriod = env.GetValue("Beam.onspillPeriod", 1.);
}

void ConfigReader::SetOffspillPeriod(const TEnv& env){
  offspillPeriod = env.GetValue("Beam.offspillPeriod", 1.);
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
  SetNoiseRate(env);
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

float ConfigReader::GetNoiseRate() const {
  return noiseRate;
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