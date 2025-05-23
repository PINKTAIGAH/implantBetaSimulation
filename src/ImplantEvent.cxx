#include <utility>
#include <tuple>

#include "ImplantEvent.hh"

void ImplantEvent::SetEventParameters(
  std::pair<int, int> implantPosition, 
  std::pair<int, int> decayPosition,
  float implantTime,
  float decayTime,
  int MCTruthId
){
  this->implantPosition = implantPosition;
  this->decayPosition = decayPosition;
  this->implantTime = implantTime;
  this->decayTime = decayTime;
  this->MCTruthId = MCTruthId;
}

std::tuple<std::pair<int, int>, std::pair<int, int>, float, float, int> ImplantEvent::GetEventParameters() const{
  return std::make_tuple(implantPosition, decayPosition, implantTime, decayTime, MCTruthId);
}