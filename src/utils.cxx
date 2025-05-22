#include "utils.hh"

void utils::printParametersToConsole(ConfigReader& reader){

  std::cout << std::endl << "##### Parameters used for simulation ##### " << std::endl;
  std::cout << "Segmentation: \t\t\t" << reader.GetDssdSegmentation().first << ", " << reader.GetDssdSegmentation().second << std::endl;
  std::cout << "Implantation Rate: \t\t" << reader.GetImplantationRate() << std::endl;
  std::cout << "Halflife: \t\t\t" << reader.GetDecayHalflife() << std::endl;
  std::cout << "Onspill: \t\t\t" << reader.GetOnspillPeriod() << std::endl;
  std::cout << "Offspill: \t\t\t" << reader.GetOffspillPeriod() << std::endl;
  std::cout << "Start Time: \t\t\t" << reader.GetStartTime() << std::endl;
  std::cout << "End Time: \t\t\t" << reader.GetEndTime() << std::endl;
  std::cout << "Correlation Window: \t\t" << reader.GetCorrelationWindow() << std::endl;
  std::cout << std::boolalpha << "Debug Mode: \t\t\t" << reader.GetDebug() << std::endl << std::endl;

}