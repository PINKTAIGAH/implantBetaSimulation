#ifndef IMPLANTATION_EVENT_H
#define IMPLANTATION_EVENT_H

#include <utility>
#include <tuple>

// !!! IDEA !!!
// Add a < operator in ImplantEvent struct so  sets are ordered by MCId
struct ImplantEvent{

  std::pair<int, int> implantPosition; 
  float implantTime;
  int MCTruthId;

  // Setters
  void SetEventParameters(
    std::pair<int, int> implantPosition, 
    float implantTime,
    int MCTruthId
  );

  // Getters
  std::tuple<std::pair<int, int>, float, int> GetEventParameters() const;

};


#endif