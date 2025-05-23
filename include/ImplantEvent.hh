#ifndef IMPLANTATION_EVENT_H
#define IMPLANTATION_EVENT_H

#include <utility>
#include <tuple>

struct ImplantEvent{

  std::pair<int, int> implantPosition; 
  std::pair<int, int> decayPosition; 
  float implantTime;
  float decayTime; 
  int MCTruthId;

  // Setters
  void SetEventParameters(
    std::pair<int, int> implantPosition, 
    std::pair<int, int> decayPosition,
    float implantTime,
    float decayTime,
    int MCTruthId
  );

  // Getters
  std::tuple<std::pair<int, int>, std::pair<int, int>, float, float, int> GetEventParameters() const;

};


#endif