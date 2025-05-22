/********************************************************************************\
 *  This is a trial code for implant beta montecarlo simulation compiled in c++ *
 *                                                                              *
 *                                                                              *
 *                                                                              *
 *                                                                              *
\********************************************************************************/

#include <iostream>
#include "ConfigReader.hh"

int main(int argc, char* argv[]){

  ConfigReader reader;
  reader.LoadConfig("./config/parameters.conf");
  
  std::cout << std::endl << "Segmentation: " << reader.GetDssdSegmentation().first << ", " << reader.GetDssdSegmentation().second << std::endl;
  std::cout << "Implantation Rate: " << reader.GetImplantationRate() << std::endl;
  std::cout << "Halflife: " << reader.GetDecayHalflife() << std::endl;
  std::cout << "Onspill: " << reader.GetOnspillPeriod() << std::endl;
  std::cout << "Offspill: " << reader.GetOffspillPeriod() << std::endl << std::endl;

  return 0;
}