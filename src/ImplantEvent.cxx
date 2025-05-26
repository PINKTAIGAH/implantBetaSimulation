#include <utility>
#include <tuple>

#include "ImplantEvent.hh"

void ImplantEvent::SetEventParameters(
  std::pair<int, int> implantPosition, 
  float implantTime,
  int MCTruthId
){
  this->implantPosition = implantPosition;
  this->implantTime = implantTime;
  this->MCTruthId = MCTruthId;
}

std::tuple<std::pair<int, int>, float, int> ImplantEvent::GetEventParameters() const{
  return std::make_tuple(implantPosition, implantTime, MCTruthId);
}