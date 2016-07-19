#ifndef CONFIGURATION_H
#define CONFIGURATION_H
#include <fstream>
#include "json/json.h"
#include "oxygine-framework.h"

class Configuration
{
private:
    std::string m_config_path;
    Json::Value m_config;
public:
    Configuration(const std::string& configfile);
    ~Configuration();
    bool load();
    void save();

    int getMusicVolume();
    void setMusicVolume(unsigned int volume);

    int getFxVolume();
    void setFxVolume(int volume);

    bool getFullScreen();
    void setFullScreen(bool isfullscreen);
};

#endif // CONFIGURATION_H
