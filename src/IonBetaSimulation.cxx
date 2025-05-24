#include <map>
#include <array>
#include <cmath>
#include <utility>
#include <vector>
#include <random>

#include "utils.hh"
#include "ImplantEvent.hh"
#include "IonBetaSimulation.hh"
#include "ExponentialGenerator.hh"
#include "GaussianGenerator.hh"


// ####### CONSTRUCTOR #######

IonBetaSimulation::IonBetaSimulation(){

  // Define default debug flag for console output
  debug = false;

  // Define default flags for class
  loadedPhysicsParameters = false;
  loadedSimulationParameters = false;
  finishedImplantEventSimulation = false;
  finishedImplantDecayCorrelation = false;

}

// ####### PRIVATE #######

std::pair<float, float> IonBetaSimulation::GetPositionOfImplant(){
  return std::make_pair(implantationPosXGenerator.Generate(), implantationPosYGenerator.Generate());
}

std::pair<float, float> IonBetaSimulation::GetPositionOfDecay(){
  return std::make_pair(decayPosGenerator.Generate(), decayPosGenerator.Generate());
}

float IonBetaSimulation::GetTimeOfImplant(float currentTime){
  return currentTime + implantationTimeGenerator.Generate();
}

float IonBetaSimulation::GetTimeOfDecay(float implantTime){
  return implantTime + decayTimeGenerator.Generate();
}

bool IonBetaSimulation::IsOnspill(float currentTime){

  int numSpillCycles = static_cast<int>(std::floor(currentTime/repetitionPeriod));

  if ((currentTime - numSpillCycles*repetitionPeriod) > onspillPeriod){
    return true;
  } 
  else return false;

}

std::pair<float, SpillFlag> IonBetaSimulation::FlipSpillFlag(float currentTime, float nextSpillChangeTime, SpillFlag spillFlag){

  // Spill flag ==> Offspill
  if (spillFlag == SpillFlag::ONSPILL){
    spillFlag = SpillFlag::OFFSPILL;
    nextSpillChangeTime = currentTime + offspillPeriod;
  }

  // Spill flag ==> Onspill
  if(spillFlag == SpillFlag::OFFSPILL){
    spillFlag = SpillFlag::ONSPILL;
    nextSpillChangeTime = currentTime + onspillPeriod;
  }

  return std::make_pair(nextSpillChangeTime, spillFlag);

}


// ####### PUBLIC #######

void IonBetaSimulation::SetPhysicsParameters(
  std::pair<int, int> dssdSegmentation,
  std::array<float, 4> implantationPositionCharacteristics, 
  int decayNearestNeighbours,
  float implantationRate, 
  float decayHalflife, 
  float betaEfficiency, 
  float onspillPeriod, 
  float offspillPeriod
){

  // Assign all physics parameters
  this->dssdSegmentation = dssdSegmentation;
  this->implantationPositionCharacteristics = implantationPositionCharacteristics;
  this->decayNearestNeighbours = decayNearestNeighbours;
  this->implantationRate = implantationRate;
  this->decayHalflife = decayHalflife;
  this->betaEfficiency = betaEfficiency;
  this->onspillPeriod = onspillPeriod;
  this->offspillPeriod = offspillPeriod;

  // Calculate and assign remaining parameters
  decayRate = std::log(2)/decayHalflife;
  repetitionPeriod = onspillPeriod + offspillPeriod;

  // Define Random generators 
  implantationTimeGenerator = ExponentialGenerator(implantationRate);
  decayTimeGenerator = ExponentialGenerator(decayRate);
  implantationPosXGenerator = GaussianGenerator(implantationPositionCharacteristics[0], implantationPositionCharacteristics[2]);
  implantationPosYGenerator = GaussianGenerator(implantationPositionCharacteristics[1], implantationPositionCharacteristics[3]);

  // Set filled parameter flag
  loadedPhysicsParameters = true;

}

void IonBetaSimulation::SetSimulationParameters(
  float startTime, 
  float endTime, 
  float timestep,
  float correlationWindow
){

  // Assign all simulation parameters
  this->startTime = startTime;
  this->endTime = endTime;
  this->timestep = timestep;
  this->correlationWindow = correlationWindow;

  // Set filled parameter flag
  loadedSimulationParameters = true;

}

void IonBetaSimulation::SetDebugPreference(bool debug){
  this->debug = debug;
}

void IonBetaSimulation::SimulateImplantEvents(int implantLimit){

  // Define local scope parameters
  double currentTime = startTime;
  float lastImplantTime = 0.;
  float nextImplantTime = -1.;
  float nextSpillChangeTime = onspillPeriod;
  float lastDecayTime = 0.;
  int MCId = 0;
  SpillFlag spillFlag = SpillFlag::OFFSPILL;
  ImplantEvent lastImplantEvent;
  std::pair<int, int> lastImplantPosition;
  std::pair<int, int> lastDecayRelativePosition;
  std::pair<int, int> lastDecayPosition;

  while( currentTime < endTime ){

    if (implantLimit > 0 && MCId >= implantLimit ) break;

    currentTime = currentTime + timestep; // Update time

    // Create new implant event
    if ( currentTime > nextImplantTime ){
      // Update Implant parameters
      ++MCId;
      lastImplantTime = currentTime;
      nextImplantTime = GetTimeOfImplant(currentTime);
      lastDecayTime = GetTimeOfDecay(currentTime);
      lastImplantPosition = GetPositionOfImplant();

      // !!! IDEA !!!
      // Fold the relativePosition -> AbsolutePosition calc. for decays in the GetPosition() method
      lastDecayRelativePosition = GetPositionOfDecay();
      lastDecayPosition = std::make_pair(lastImplantPosition.first + lastDecayRelativePosition.first, lastImplantPosition.second + lastDecayRelativePosition.second);

      // Create ImplantEvent and store it.
      lastImplantEvent.SetEventParameters(lastImplantPosition, lastDecayPosition, lastImplantTime, lastDecayTime, MCId);
      implantEventVector.emplace_back(lastImplantEvent);

      if (debug) utils::printImplantEvent(lastImplantEvent); // Print out Event

      // Change spill flag if needed
      if (currentTime > nextSpillChangeTime) {
        std::pair<float, SpillFlag> methodOut = FlipSpillFlag(currentTime, nextSpillChangeTime, spillFlag);
        nextSpillChangeTime = methodOut.first;
        spillFlag = methodOut.second;
      }

    }

  }

}

