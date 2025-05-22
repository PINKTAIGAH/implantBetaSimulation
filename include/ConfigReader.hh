#ifndef CONFIG_READER_H
#define CONFING_READER_H

#include <TEnv.h>
#include <pair>
#include <string>

class ConfigReader{
  
  public:

    ConfigReader(const std::string& configFile)

    // Getters for parameters in config
    std::pair<int, int> GetDssdSegmentation() const;
    float GetImplantationRate() const;
    float GetDecayHalflife() const;
    // ...

  private:

    // internal parameters for config values
    std::pair<int, int> dssdSegmentation;
    float implantationRate;
    float decayHalflife;
    // ...

    // Method to load in the config file
    void LoadConfig(const std::string& configFile);

    // Setters for each parameter passing TEnv as parameter
    void SetDssdSegmentation(const TEnv& env);
    void SetImplantationRate(const TEnv& env);
    void SetDecayHalflife(const TEnv& env);
    // ...

} 


#endif