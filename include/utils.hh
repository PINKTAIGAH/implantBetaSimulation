#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "ConfigReader.hh"
#include "ImplantEvent.hh"

namespace utils{
    
    void printParameters(ConfigReader& reader);
    void printImplantEvent(ImplantEvent& implantEvent);
    void printImplantDecayCorrelation(float& ionBetaTimediff);

}

#endif
