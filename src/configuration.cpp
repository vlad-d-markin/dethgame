#include "configuration.h"

Configuration::Configuration(const std::string& configfile): m_config_path(configfile) {}

Configuration::~Configuration() {}

bool Configuration::load()
{
    if (!oxygine::file::exists(m_config_path.c_str()))
        return false;

    oxygine::file::buffer bf;
    oxygine::file::read(m_config_path.c_str(), bf);
    //parse
    Json::Reader reader;
    reader.parse((char*)&bf.front(), (char*)&bf.front() + bf.size(), m_config, false);
    return true;
}

void Configuration::save()
{
    Json::FastWriter writer;
    std::string s = writer.write(m_config);
    oxygine::log::messageln("%s",s.c_str());

    std::ofstream config_file;
    config_file.open(m_config_path);
    config_file << s;
    config_file.close();
}

int Configuration::getMusicVolume()
{
    return(m_config.get("music_volume", "100").asInt());
}

void Configuration::setMusicVolume(unsigned int volume)
{
    m_config["music_volume"] = volume;
}

bool Configuration::getFullScreen()
{
    return(m_config.get("full_screen", false).asBool());
}

void Configuration::setFullScreen(bool isfullscreen)
{
    m_config["full_screen"] = isfullscreen;
}

void Configuration::setFxVolume(int volume)
{
    m_config["fx_volume"] = volume;
}

int Configuration::getFxVolume()
{
    return(m_config.get("fx_volume", 100).asInt());
}
