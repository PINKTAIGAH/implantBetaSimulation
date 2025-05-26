#include <utility>
#include <tuple>

#include "DecayEvent.hh"
#include "MatchedEvent.hh"

void MatchedImplantEvent::SetEventParameters(
  std::pair<int, int> matchedDecayMultiplicity,
  std::pair<int, int> implantPosition,
  float implantTime,
  int MCTruthId
){
  this->matchedDecayMultiplicity = matchedDecayMultiplicity;
  this->implantPosition = implantPosition;
  this->implantTime = implantTime;
  this->MCTruthId = MCTruthId;
}

void MatchedImplantEvent::SetMatchedDecayVector(std::vector<MatchedDecayEvent> matchedDecayVector){
  this->matchedDecayVector = matchedDecayVector;
}

std::tuple<std::pair<int, int>, std::pair<int, int>, float, int> MatchedImplantEvent::GetEventParameters() const{
  return std::make_tuple(matchedDecayMultiplicity, implantPosition, implantTime, MCTruthId);
}

std::vector<MatchedDecayEvent> MatchedImplantEvent::GetMatchedDecayVector() const {
  return matchedDecayVector;
}


void MatchedDecayEvent::SetEventParameters(
  CorrelationType correlationType, 
  DecayType decayType,
  std::pair<int, int> decayPosition,
  float decayTime,
  int MCTruthId,
  int matchOrder
){
  this->correlationType = correlationType;
  this->decayType = decayType;
  this->decayPosition = decayPosition;
  this->decayTime = decayTime;
  this->MCTruthId = MCTruthId;
  this->matchOrder = matchOrder;
}

std::tuple<CorrelationType, DecayType, std::pair<int, int>, float, int, int> MatchedDecayEvent::GetEventParameters() const{
  return std::make_tuple(correlationType, decayType, decayPosition, decayTime, MCTruthId, matchOrder);
}