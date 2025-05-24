/********************************************************************************\
 *  This is a trial code for implant beta montecarlo simulation compiled in c++ *
 *                                                                              *
 *                                                                              *
 *                                                                              *
 *                                                                              *
\********************************************************************************/

#include <iostream>
#include "ConfigReader.hh"
#include "IonBetaSimulation.hh"
#include "utils.hh"

int main(int argc, char* argv[]){

  // Initialise config reader object and read the parameters
  ConfigReader reader;
  reader.LoadConfig("./config/parameters.conf");
  
  // Print out the parameters used for the experiment
  utils::printParameters(reader);

  // Initialise simulator and set parameters
  IonBetaSimulation simulator;
  simulator.SetDebugPreference(reader.GetDebug());
  simulator.SetPhysicsParameters(
    reader.GetDssdSegmentation(),
    reader.GetImplantationPositionCharacteristics(),
    reader.GetDecayNearestNeighbours(),
    reader.GetImplantationRate(),
    reader.GetDecayHalflife(),
    reader.GetBetaEfficiency(),
    reader.GetOnspillPeriod(),
    reader.GetOffspillPeriod()
  );
  simulator.SetSimulationParameters(
    reader.GetStartTime(),
    reader.GetEndTime(),
    reader.GetTimestep(),
    reader.GetCorrelationWindow()
  );

  // Simulate Implants & Decays
  simulator.SimulateImplantEvents();

  std::cout << "Simulation has run succesfully. Goodbye!" << std::endl << std::endl;


  return 0;
}