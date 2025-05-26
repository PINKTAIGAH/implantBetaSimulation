#include <utility>
#include <tuple>

#include "DecayEvent.hh"

void DecayEvent::SetEventParameters(
  DecayType decayType,
  std::pair<int, int> decayPosition,
  float decayTime,
  int MCTruthId
){
  this->decayType = decayType;
  this->decayPosition = decayPosition;
  this->decayTime = decayTime;
  this->MCTruthId = MCTruthId;
}

std::tuple<DecayType, std::pair<int, int>, float, int> DecayEvent::GetEventParameters() const{
  return std::make_tuple(decayType, decayPosition, decayTime, MCTruthId);
}