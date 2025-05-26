#include <tuple>
#include <string>

#include "utils.hh"
#include "ImplantEvent.hh"
#include "MatchedEvent.hh"
#include "IonBetaSimulation.hh"

void utils::printParameters(ConfigReader& reader){

  const auto& implantPosChar = reader.GetImplantationPositionCharacteristics();

  std::cout << std::endl << "##### Parameters used for simulation ##### " << std::endl;
  std::cout << "Segmentation: \t\t\t" << reader.GetDssdSegmentation().first << ", " << reader.GetDssdSegmentation().second << std::endl;
  std::cout << "Noise Rate: \t\t\t" << reader.GetNoiseRate() << std::endl;
  std::cout << "Implantation Pos.:\t\t" << implantPosChar[0] << ", " << implantPosChar[1] << ", " << implantPosChar[2] << ", " << implantPosChar[3] << std::endl;
  std::cout << "Decay Nearest Neighbour: \t" << reader.GetDecayNearestNeighbours() << std::endl;
  std::cout << "Implantation Rate: \t\t" << reader.GetImplantationRate() << std::endl;
  std::cout << "Halflife: \t\t\t" << reader.GetDecayHalflife() << std::endl;
  std::cout << "Beta Eff.: \t\t\t" << reader.GetBetaEfficiency() << std::endl;
  std::cout << "Onspill: \t\t\t" << reader.GetOnspillPeriod() << std::endl;
  std::cout << "Offspill: \t\t\t" << reader.GetOffspillPeriod() << std::endl;
  std::cout << "Start Time: \t\t\t" << reader.GetStartTime() << std::endl;
  std::cout << "End Time: \t\t\t" << reader.GetEndTime() << std::endl;
  std::cout << "Timestep: \t\t\t" << reader.GetTimestep() << std::endl;
  std::cout << "Correlation Window: \t\t" << reader.GetCorrelationWindow() << std::endl;
  std::cout << std::boolalpha << "Debug Mode: \t\t\t" << reader.GetDebug() << std::endl << std::endl;

}

void utils::printImplantEvent(ImplantEvent& implantEvent, DecayEvent& decayEvent){

  const auto& [implantPosition, implantTime, implantMCTruthId] = implantEvent.GetEventParameters();
  const auto& [decayType, decayPosition, decayTime, decayMCTruthId] = decayEvent.GetEventParameters();

  std::cout << "[DEBUG] IMPLANT EVENT GENERATED ### MCTruthId: " << implantMCTruthId << " (" << decayMCTruthId << ") ### Imp. Pos.: (" << implantPosition.first << "," << implantPosition.second \
    << ") ### Decay Pos.: (" << decayPosition.first << "," << decayPosition.second << ") ### Imp. Time: " << implantTime \
    << " ### Decay Time: " << decayTime << std::endl;

}

void utils::printNoiseEvent(DecayEvent& noiseEvent){

  const auto& [noiseType, noisePosition, noiseTime, noiseMCTruthId] = noiseEvent.GetEventParameters();

  std::cout << "[DEBUG] NOISE EVENT GENERATED ### MCTruthId: " << noiseMCTruthId << " ### Noise Pos.: (" << noisePosition.first << "," << noisePosition.second << \
    ") ### Noise Time: " << noiseTime << std::endl;

}

void utils::printImplantDecayCorrelation(MatchedDecayEvent& matchedDecayEvent, int& implantMCId, std::string& correlationType, std::string& decayType){

  std::cout << "[DEBUG] DECAY EVENT CORRELATED ### Corr. Type: " << correlationType << " ### Decay Type: " << decayType << " ### Decay Time: " \
    << matchedDecayEvent.decayTime << " ### Match Order: " << matchedDecayEvent.matchOrder << " ### MC_ID: " << matchedDecayEvent.MCTruthId << " (" \
    << implantMCId << ")" << std::endl; 

}

void utils::printMatchedImplantSummary(MatchedImplantEvent& matchedImplantEvent){

  std::cout << "[DEBUG] IMPLANT EVENT SUMMARY ### Fwd. Multiplicity: " << matchedImplantEvent.matchedDecayMultiplicity.first << " ### Bkw Multiplicity: " \
    << matchedImplantEvent.matchedDecayMultiplicity.second << std::endl;

}