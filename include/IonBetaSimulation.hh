#ifndef ION_BETA_SIMULATION_H
#define ION_BETA_SIMULATION_H

#include <array>
#include <utility>
#include <vector>

#include "utils.hh"
#include "ImplantEvent.hh"
#include "ExponentialGenerator.hh"
#include "GaussianGenerator.hh"
#include "DiscreteGenerator.hh"


// DEFINE GLOBAL SPILLFLAGS
enum class SpillFlag {ONSPILL, OFFSPILL};

class IonBetaSimulation{

  public:

    IonBetaSimulation();

    // Parameter Setters
    void SetPhysicsParameters(
      std::pair<int, int> dssdSegmentation,
      std::array<float, 4> implantataionPositionCharacteristics, 
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

    // Parameter Getters
    std::vector<ImplantEvent> GetImplantEvents() const; 
    std::vector<float> GetImplantDecayCorrelations() const; 

    // Simulation Calls
    void SimulateImplantEvents(int implantLimit=-1);
    void CorrelateImplantDecays(bool firstMatch=false);

  private:

    // Physics parameters
    std::pair<int, int> dssdSegmentation;
    std::array<float, 4> implantationPositionCharacteristics;
    int decayNearestNeighbours;
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
    std::vector<ImplantEvent> implantEventVector; // Not defined in config
    std::vector<float> implantDecayTimedifferencesVector; // Not defined in config

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
    GaussianGenerator implantationPosXGenerator; // Not defined in config
    GaussianGenerator implantationPosYGenerator; // Not defined in config
    DiscreteGenerator decayPosGenerator; // Not defined in config

    // Private Class Methods
    std::pair<float, float> GetPositionOfImplant();
    std::pair<float, float> GetPositionOfDecay();
    float GetTimeOfImplant(float currentTime);
    float GetTimeOfDecay(float implantTime);
    bool IsOnspill(float currentTime);
    std::pair<float, SpillFlag> FlipSpillFlag(float currentTime, float nextSpillChangeTime, SpillFlag spillFlag);

};



#endif