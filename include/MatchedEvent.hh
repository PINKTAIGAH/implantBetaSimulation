#ifndef MATCHED_EVENT_H
#define MATCHED_EVENT_H

#include <utility>
#include <tuple>
#include <vector>

#include "DecayEvent.hh"

enum class CorrelationType {FORWARD, BACKWARD};

struct MatchedDecayEvent{

  CorrelationType correlationType;
  DecayType decayType;
  std::pair<int, int> decayPosition; 
  float decayTime; 
  int MCTruthId;
  int matchOrder;


  // Setters
  void SetEventParameters(
    CorrelationType correlationType,
    DecayType decayType,
    std::pair<int, int> decayPosition,
    float decayTime,
    int MCTruthId,
    int matchOrder
  );

  // Getters
  std::tuple<CorrelationType, DecayType, std::pair<int, int>, float, int, int> GetEventParameters() const;
};



struct MatchedImplantEvent{

  std::pair<int, int> matchedDecayMultiplicity; // pair<forwardMultiplicity, backwardsMultiplicity>
  std::pair<int, int> implantPosition; 
  float implantTime; 
  int MCTruthId;
  std::vector<MatchedDecayEvent> matchedDecayVector;

  // Setters
  void SetEventParameters(
    std::pair<int, int> matchedDecayMultiplicity,
    std::pair<int, int> implantPosition,
    float implantTime,
    int MCTruthId
  );

  void SetMatchedDecayVector(std::vector<MatchedDecayEvent> matchedDecayVector);

  // Getters
  std::tuple<std::pair<int, int>, std::pair<int, int>, float, int> GetEventParameters() const;
  std::vector<MatchedDecayEvent> GetMatchedDecayVector() const;

};

#endif