#ifndef DECAY_EVENT_H
#define DECAY_EVENT_H

#include <utility>
#include <tuple>

enum class DecayType {BETA, NOISE};

// !!! IDEA !!!
// Add a < operator in DecayEvent struct so  sets are ordered by MCId
struct DecayEvent{

  DecayType decayType;
  std::pair<int, int> decayPosition; 
  float decayTime; 

  int MCTruthId;

  // Setters
  void SetEventParameters(
    DecayType decayType,
    std::pair<int, int> decayPosition,
    float decayTime,
    int MCTruthId
  );

  // Getters
  std::tuple<DecayType, std::pair<int, int>, float, int> GetEventParameters() const;

};


#endif