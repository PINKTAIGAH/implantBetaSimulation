#include <map>
#include <array>
#include <cmath>
#include <utility>
#include <vector>
#include <random>

#include "utils.hh"
#include "ImplantEvent.hh"
#include "DecayEvent.hh"
#include "MatchedEvent.hh"
#include "IonBetaSimulation.hh"
#include "ExponentialGenerator.hh"
#include "GaussianGenerator.hh"
#include "DiscreteGenerator.hh"
#include "BetaPositionGenerator.hh"


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

std::pair<float, float> IonBetaSimulation::GetPositionOfNoise(){
  return std::make_pair(noisePosXGenerator.Generate(), noisePosYGenerator.Generate());
}

float IonBetaSimulation::GetTimeOfImplant(float currentTime){
  return currentTime + implantationTimeGenerator.Generate();
}

float IonBetaSimulation::GetTimeOfDecay(float implantTime){
  return implantTime + decayTimeGenerator.Generate();
}

float IonBetaSimulation::GetTimeOfNoise(float currentTime){
  return currentTime + noiseTimeGenerator.Generate();
}

bool IonBetaSimulation::IsOnspill(float currentTime){

  int numSpillCycles = static_cast<int>(std::floor(currentTime/repetitionPeriod));

  if ((currentTime - numSpillCycles*repetitionPeriod) > onspillPeriod){
    return true;
  } 
  else return false;

}

std::pair<float, SpillFlag> IonBetaSimulation::FlipSpillFlag(float currentTime, float spillChangeTime, SpillFlag lastSpillflag){

  float nextSpillChangeTime;
  SpillFlag nextSpillflag;

  switch (lastSpillflag){

    case SpillFlag::ONSPILL:{
      nextSpillflag = SpillFlag::OFFSPILL;
      nextSpillChangeTime = currentTime + offspillPeriod;
      break;
    }

    case SpillFlag::OFFSPILL:{
      nextSpillflag = SpillFlag::ONSPILL;
      nextSpillChangeTime = currentTime + onspillPeriod;
      break;
    }
  }

  return std::make_pair(nextSpillChangeTime, nextSpillflag);

}

bool IonBetaSimulation::IsDecayDetected(){
  return betaEffiencyGenerator.Generate() <= betaEfficiency;
}

void IonBetaSimulation::MergeBetasAndNoiseEvents(){
  
  // Add Noise events to map
  for ( const auto& noiseItr : noiseEventMap ){
    // NOTE : NoiseItr is map<time, DecayEvent>
    efficiencyCorrectedDecayEventMap.emplace(noiseItr.first, noiseItr.second);
  }
  
  // Add Beta events to map
  for ( const auto& betaItr : betaEventMap ){
    // NOTE : impDecayItr is pair<ImplantEvent, DecayEvent>
    if ( !IsDecayDetected() ) continue; // Skip event if not detected by DSSSD
    efficiencyCorrectedDecayEventMap.emplace(betaItr.first, betaItr.second);
  }

}


// ####### PUBLIC #######

void IonBetaSimulation::SetPhysicsParameters(
  std::pair<int, int> dssdSegmentation,
  std::array<float, 4> implantationPositionCharacteristics, 
  float noiseRate,
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
  this->noiseRate = noiseRate;
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
  noiseTimeGenerator = ExponentialGenerator(noiseRate);
  noisePosXGenerator = DiscreteGenerator(1, implantationPositionCharacteristics[0]);
  noisePosYGenerator = DiscreteGenerator(1, implantationPositionCharacteristics[1]);
  betaEffiencyGenerator = UniformGenerator(0., 1.); 

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
  float lastNoiseTime = 0.;
  float nextNoiseTime = -1.;
  float nextImplantTime = -1.;
  float nextSpillChangeTime = onspillPeriod;
  float lastBetaTime = 0.;
  int MCId = 0;
  SpillFlag spillflag = SpillFlag::OFFSPILL;
  ImplantEvent lastImplantEvent;
  DecayEvent lastBetaEvent;
  DecayEvent lastNoiseEvent;
  
  std::pair<int, int> lastImplantPosition;
  std::pair<int, int> lastNoisePosition;
  std::pair<int, int> lastBetaRelativePosition;
  std::pair<int, int> lastBetaPosition;

  while( currentTime < endTime ){

    if (implantLimit > 0 && MCId >= implantLimit ) break;

    currentTime = currentTime + timestep; // Update time

    // [LOOP] -> Create new Implant + Decay event pair
    if ( currentTime > nextImplantTime && spillflag == SpillFlag::ONSPILL){
      // Update Implant parameters
      ++MCId;
      lastImplantTime = currentTime;
      nextImplantTime = GetTimeOfImplant(currentTime);
      lastBetaTime = GetTimeOfDecay(currentTime);
      lastImplantPosition = GetPositionOfImplant();

      // Log implant in timerange manager
      deadtimeManager.addRange(currentTime, currentTime+deadtimeWindow, lastImplantPosition.first, lastImplantPosition.second);

      // !!! IDEA !!!
      // Fold the relativePosition -> AbsolutePosition calc. for decays in the GetPosition() method
      lastBetaRelativePosition = GetPositionOfDecay();
      lastBetaPosition = std::make_pair(lastImplantPosition.first + lastBetaRelativePosition.first, lastImplantPosition.second + lastBetaRelativePosition.second);

      // Create ImplantEvent and store it.
      lastImplantEvent.SetEventParameters(lastImplantPosition, lastImplantTime, MCId);
      lastBetaEvent.SetEventParameters(DecayType::BETA, lastBetaPosition, lastBetaTime, MCId);
      implantEventMap.emplace(lastImplantTime, lastImplantEvent);
      betaEventMap.emplace(lastBetaTime, lastBetaEvent);

      if (debug) utils::printImplantEvent(lastImplantEvent, lastBetaEvent); // Print out Event

    }

    // [LOOP] -> Create new Noise event
    if (currentTime > nextNoiseTime){
      // Update parameters
      lastNoiseTime = currentTime;
      nextNoiseTime = GetTimeOfNoise(currentTime);
      lastNoisePosition = GetPositionOfNoise();

      // Create Noise Event and store it
      // Nosie events have MCID = -999 assigend to them (no implant correlation)
      lastNoiseEvent.SetEventParameters(DecayType::NOISE, lastNoisePosition, lastNoiseTime, -999);
      noiseEventMap.emplace(lastNoiseTime, lastNoiseEvent);

      if (debug) utils::printNoiseEvent(lastNoiseEvent); // Print out event

    }

    // [CHECK] -> Change spill flag if needed
    if (currentTime > nextSpillChangeTime) {
      std::pair<float, SpillFlag> methodOut = FlipSpillFlag(currentTime, nextSpillChangeTime, spillflag);
      nextSpillChangeTime = methodOut.first;
      spillflag = methodOut.second;
      
    }

  }

  // Flip simulation bool
  finishedImplantEventSimulation = true;

}

void IonBetaSimulation::CorrelateImplantDecays(){

  // Merge noise with beta events (w/ detector efficiency)
  MergeBetasAndNoiseEvents();

  // Correlate decays to implant based on position && time correlation 
  // [LOOP] -> Loop over all implants
  for (const auto& implantItr : implantEventMap ){

    // Define counters for forward and backward matches
    int forwardMatchCounter = 0;
    int backwardMatchCounter = 0;
    
    // Unpack all implant parameters
    ImplantEvent implantEvt = implantItr.second;
    auto& [implantPosition, implantTime, implantMCId] = implantEvt;

    // Make vector of all Matched Decays
    std::vector<MatchedDecayEvent> matchedDecayVector;

    // [LOOP] -> Loop through all decays occuring after implant within [implantTime, implantTime+correlationWindow]
    auto lowerBoundForward = efficiencyCorrectedDecayEventMap.lower_bound(implantTime);
    auto upperBoundForward = efficiencyCorrectedDecayEventMap.upper_bound(implantTime + correlationWindow);
    
    for (auto decayItr = lowerBoundForward; decayItr != upperBoundForward; ++decayItr){

      // Unpack all decay parameters
      DecayEvent decayEvt = decayItr->second;
      auto& [decayType, decayPosition, decayTime, decayMCId] = decayEvt;

      // Veto decay event if inside of implant deadtime
      if ( deadtimeManager.contains(decayTime, decayPosition.first, decayPosition.second) ) continue;
      
      // Check if decay event occures within position threshold (1 nearest neighbour) from implant
      if ( std::abs(decayPosition.first - implantPosition.first) <= 1 && std::abs(decayPosition.second - implantPosition.second) <= 1 ){
        
        ++forwardMatchCounter;

        MatchedDecayEvent matchedDecay;
        matchedDecay.SetEventParameters(CorrelationType::FORWARD, decayType, decayPosition, decayTime, decayMCId, forwardMatchCounter);
        matchedDecayVector.emplace_back(matchedDecay);

        // Add Match to vector
        float timediff = decayTime-implantTime;
        if (forwardMatchCounter == 1) implantDecayTimediffFirstVector.emplace_back(timediff); // Add to first match vector
        implantDecayTimediffAllVector.emplace_back(timediff); // Add to all match vector

        if (debug) {
          std::string correlationTypeString = "FORWARD";
          std::string betaTypeString = (decayType == DecayType::BETA) ? "BETA" : "NOISE";
          utils::printImplantDecayCorrelation(matchedDecay, implantMCId, correlationTypeString, betaTypeString);
        }

      }
    }

    // [LOOP] -> Loop through all decays occuring before implant within [implantTime-correlationWindow, implantTime]
    auto upperBoundBackward = efficiencyCorrectedDecayEventMap.lower_bound(implantTime);
    auto lowerBoundBackward = efficiencyCorrectedDecayEventMap.lower_bound(implantTime - correlationWindow);

    auto rbegin = std::make_reverse_iterator(upperBoundBackward);
    auto rend = std::make_reverse_iterator(lowerBoundBackward);
    
    for (auto decayRItr = lowerBoundBackward; decayRItr != upperBoundBackward; ++decayRItr){

      // Unpack all decay parameters
      DecayEvent decayEvt = decayRItr->second;
      auto& [decayType, decayPosition, decayTime, decayMCId] = decayEvt;

      // IDEA!!! Do we add deadtimeManager veto here too? (Prob not as no decay rate increase influenced by imps in backwards direction)
      
      // Check if decay event occures within position threshold (1 nearest neighbour) from implant
      if ( std::abs(decayPosition.first - implantPosition.first) <= 1 && std::abs(decayPosition.second - implantPosition.second) <= 1 ){
        
        ++backwardMatchCounter;

        MatchedDecayEvent matchedDecay;
        matchedDecay.SetEventParameters(CorrelationType::BACKWARD, decayType, decayPosition, decayTime, decayMCId, backwardMatchCounter);
        matchedDecayVector.emplace_back(matchedDecay);

        // Add Match to map
        float timediff = decayTime-implantTime;
        if (backwardMatchCounter == 1) implantDecayTimediffFirstVector.emplace_back(timediff); // Add to first match vector
        implantDecayTimediffAllVector.emplace_back(timediff); // Add to all match vector

        if (debug) {
          std::string correlationTypeString = "BACKWARD";
          std::string betaTypeString = (decayType == DecayType::BETA) ? "BETA" : "NOISE";
          utils::printImplantDecayCorrelation(matchedDecay, implantMCId, correlationTypeString, betaTypeString);
        }

      }

    }

    // Now we have processed all matched decays, build matchedImplantEvent and append to vector
    MatchedImplantEvent matchedImplantEvent;
    matchedImplantEvent.SetEventParameters(std::make_pair(forwardMatchCounter, backwardMatchCounter), implantPosition, implantTime, implantMCId);
    matchedImplantEvent.SetMatchedDecayVector(matchedDecayVector);

    matchedEventVector.emplace_back(matchedImplantEvent);

    if (debug) utils::printMatchedImplantSummary(matchedImplantEvent);

  }

  // Flip correlation bool
  finishedImplantDecayCorrelation = true;

}

std::vector<MatchedImplantEvent> IonBetaSimulation::GetMatchedEventVector() const {
  return matchedEventVector;
}

std::vector<float> IonBetaSimulation::GetImplantDecayTimediffAll() const {
  return implantDecayTimediffAllVector;
}

std::vector<float> IonBetaSimulation::GetImplantDecayTimediffFirst() const {
  return implantDecayTimediffFirstVector;
}

