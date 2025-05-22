/********************************************************************************\
 *  This is a trial code for implant beta montecarlo simulation compiled in c++ *
 *                                                                              *
 *                                                                              *
 *                                                                              *
 *                                                                              *
\********************************************************************************/

#include <iostream>
#include "ConfigReader.hh"
#include "utils.hh"

int main(int argc, char* argv[]){

  // Initialise config reader object and read the parameters
  ConfigReader reader;
  reader.LoadConfig("./config/parameters.conf");
  
  // Print out the parameters used for the experiment
  utils::printParametersToConsole(reader);

  return 0;
}