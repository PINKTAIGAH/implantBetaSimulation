#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>

#include "ConfigReader.hh"
#include "ImplantEvent.hh"
#include "DecayEvent.hh"
#include "MatchedEvent.hh"
#include "IonBetaSimulation.hh"

namespace utils{
    
    void printParameters(ConfigReader& reader);
    void printImplantEvent(ImplantEvent& implantEvent, DecayEvent& DecayEvent);
    void printNoiseEvent(DecayEvent& noiseEvent);
    void printImplantDecayCorrelation(MatchedDecayEvent& matchedDecayEvent, int& implantMCId, std::string& correlationType, std::string& decayType);
    void printMatchedImplantParameters(MatchedImplantEvent& matchedImplantEvent);

}

#endif
