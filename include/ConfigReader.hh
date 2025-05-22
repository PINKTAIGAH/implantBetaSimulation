#ifndef CONFIG_READER_H
#define CONFIG_READER_H

#include <TEnv.h>
#include <utility>
#include <string>

class ConfigReader{
  
  public:

    ConfigReader();

    // Method to load in the config file
    void LoadConfig(const std::string configFile);

    // Getters for parameters in config
    std::pair<int, int> GetDssdSegmentation() const;
    float GetImplantationRate() const;
    float GetDecayHalflife() const;
    float GetOnspillPeriod() const;
    float GetOffspillPeriod() const;
    // ...

  private:

    // internal parameters for config values
    std::pair<int, int> dssdSegmentation;
    float implantationRate;
    float decayHalflife;
    float onspillPeriod;
    float offspillPeriod;
    // ...

    // Setters for each parameter passing TEnv as parameter
    void SetDssdSegmentation(const TEnv& env);
    void SetImplantationRate(const TEnv& env);
    void SetDecayHalflife(const TEnv& env);
    void SetOnspillPeriod(const TEnv& env);
    void SetOffspillPeriod(const TEnv& env);
    // ...

};


#endif