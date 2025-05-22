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
    float GetStartTime() const;
    float GetEndTime() const;
    float GetCorrelationWindow() const;
    bool GetDebug() const;
    // ...

  private:

    // internal parameters for config values
    std::pair<int, int> dssdSegmentation;
    float implantationRate;
    float decayHalflife;
    float onspillPeriod;
    float offspillPeriod;
    float startTime;
    float endTime;
    float timestep;
    float correlationWindow;
    bool debug;
    // ...

    // Setters for each parameter passing TEnv as parameter
    void SetDssdSegmentation(const TEnv& env);
    void SetImplantationRate(const TEnv& env);
    void SetDecayHalflife(const TEnv& env);
    void SetOnspillPeriod(const TEnv& env);
    void SetOffspillPeriod(const TEnv& env);
    void SetStartTime(const TEnv& env);
    void SetEndTime(const TEnv& env);
    void SetCorrelationWindow(const TEnv& env);
    void SetDebug(const TEnv& env);
    // ...

};


#endif