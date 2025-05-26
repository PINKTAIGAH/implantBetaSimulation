#ifndef ION_BETA_SIMULATION_H
#define ION_BETA_SIMULATION_H

#include <map>
#include <array>
#include <utility>
#include <vector>

#include "utils.hh"
#include "ImplantEvent.hh"
#include "DecayEvent.hh"
#include "MatchedEvent.hh"
#include "ExponentialGenerator.hh"
#include "GaussianGenerator.hh"
#include "DiscreteGenerator.hh"
#include "BetaPositionGenerator.hh"
#include "UniformGenerator.hh"


// DEFINE GLOBAL SPILLFLAGS
enum class SpillFlag {ONSPILL, OFFSPILL};

class IonBetaSimulation{

  public:

    IonBetaSimulation();

    // Parameter Setters
    void SetPhysicsParameters(
      std::pair<int, int> dssdSegmentation,
      std::array<float, 4> implantataionPositionCharacteristics, 
      float noiseRate,
      int decayNearestNeighbours,
      float implantationRate, 
      float decayHalflife, 
      float betaEfficiency, 
      float onspillPeriod, 
      float offspillPeriod
    );
    void SetSimulationParameters(
      float startTime, 
      float endTime, 
      float timestep,
      float correlationWindow
    );
    void SetDebugPreference(bool debug);

    // Simulation Calls
    void SimulateImplantEvents(int implantLimit=-1);
    void CorrelateImplantDecays();

    std::vector<MatchedImplantEvent> GetMatchedEventVector() const;
    std::vector<float> GetImplantDecayTimediffAll() const;
    std::vector<float> GetImplantDecayTimediffFirst() const;

  private:

    // Physics parameters
    std::pair<int, int> dssdSegmentation;
    std::array<float, 4> implantationPositionCharacteristics;
    int decayNearestNeighbours;
    float noiseRate;
    float implantationRate;
    float decayHalflife;
    float betaEfficiency;
    float onspillPeriod;
    float offspillPeriod;
    float decayRate; // Not defined in config
    float repetitionPeriod; // Not defined in config

    // Simulation parametrs
    float startTime;
    float endTime;
    float timestep;
    float correlationWindow;

    std::map<float, ImplantEvent> implantEventMap; // Not defined in config
    std::map<float, DecayEvent> noiseEventMap; // Not defined in config
    std::map<float, DecayEvent> betaEventMap; // Not defined in config
    // This map contains: EFFICENCY CORRECTED BETA + NOISE DECAY EVENTS 
    std::map<float, DecayEvent> efficiencyCorrectedDecayEventMap; // Not definded in config

    std::vector<MatchedImplantEvent> matchedEventVector;
    std::vector<float> implantDecayTimediffAllVector;
    std::vector<float> implantDecayTimediffFirstVector;

    // Debug flag
    bool debug;

    // Loaded parameters flags
    bool loadedPhysicsParameters;
    bool loadedSimulationParameters;

    // Concluded simulations
    bool finishedImplantEventSimulation;
    bool finishedImplantDecayCorrelation;

    // Random 
    ExponentialGenerator implantationTimeGenerator; // Not defined in config
    ExponentialGenerator decayTimeGenerator; // Not defined in config
    ExponentialGenerator noiseTimeGenerator; // Not defined in config
    DiscreteGenerator noisePosXGenerator; // Not defined in config
    DiscreteGenerator noisePosYGenerator; // Not defined in config
    GaussianGenerator implantationPosXGenerator; // Not defined in config
    GaussianGenerator implantationPosYGenerator; // Not defined in config
    BetaPositionGenerator decayPosGenerator; // Not defined in config
    UniformGenerator betaEffiencyGenerator; // Not defined in config

    // Private Class Methods
    std::pair<float, float> GetPositionOfImplant();
    std::pair<float, float> GetPositionOfDecay();
    std::pair<float, float> GetPositionOfNoise();
    float GetTimeOfImplant(float currentTime);
    float GetTimeOfDecay(float implantTime);
    float GetTimeOfNoise(float currentTime);
    bool IsOnspill(float currentTime);
    bool IsDecayDetected();
    void MergeBetasAndNoiseEvents();
    std::pair<float, SpillFlag> FlipSpillFlag(float currentTime, float nextSpillChangeTime, SpillFlag spillFlag);


};



#endif