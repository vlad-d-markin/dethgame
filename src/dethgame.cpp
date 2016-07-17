#include "dethgame.h"
#include <iostream>


#define MAP_TMX_PATH "map.tmx"

using namespace oxygine;

DethGame * DethGame::instance()
{
    static DethGame game;
    return &game;
}

DethGame::DethGame():config(CONFIG)
{

}

spStage DethGame::getMainStage()
{
    return getStage();
}

std::string DethGame::getGuiResPath()
{
    return "gui.xml";
}

std::string DethGame::getTileResPath()
{
    return "tile.xml";
}

std::string DethGame::getBananaResPath()
{
    return "banana.xml";
}

std::string DethGame::getMapTmxPath()
{
    return MAP_TMX_PATH;
}

int DethGame::getPlayerMaxHealth()
{
	return 500;
}

void DethGame::setFullscreen(SDL_Window* window, bool is_fullscreen)
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    Uint32 old_flags = SDL_GetWindowFlags(window);

	SDL_DisplayMode mode;
	SDL_GetCurrentDisplayMode(0, &mode);

    SDL_SetWindowFullscreen(window, is_fullscreen ? old_flags | FullscreenFlag : old_flags & ~FullscreenFlag);

	if (is_fullscreen)
	{
		SDL_SetWindowSize(window, mode.w, mode.h);
	}
	else
	{
		SDL_SetWindowSize(window, getMainStage()->getSize().x, getMainStage()->getSize().y);
	}

	if (m_optionsScreen)
	{
		m_optionsScreen->updateLayout();
	}
}

Configuration * DethGame::getConfiguration()
{
    return &config;
}


void DethGame::quit()
{
    core::requestQuit();
}

void DethGame::preInit()
{
    config.load();

}

void DethGame::init()
{
    setFullscreen(core::getWindow(), config.getFullScreen());
    m_menuScreen = new MainMenu();
    getMainStage()->addChild(m_menuScreen);
    config.setMusicVolume(78);
    oxygine::log::messageln("volume=%d",config.getMusicVolume());
//    setFullscreen(core::getWindow(), config.getFullScreen());
}

void DethGame::startGame(Event * event)
{
    m_gameScreen = new GameScreen();
    getMainStage()->addChild(m_gameScreen);
    setScreen("Game screen");
}

void DethGame::optionsScreen(Event *event)
{
    m_optionsScreen = new OptionsScreen();
    getMainStage()->addChild(m_optionsScreen);
    setScreen("Options screen");
}

void DethGame::update()
{

}

void DethGame::destroy()
{
    oxygine::log::messageln("destroy all. that's brutal");
    config.save();
}

void DethGame::setScreen(std::string name)
{
    if (name == "Menu") {
        if (getMainStage()->getChild("Game screen")) {
            m_gameScreen->setVisible(false);
            m_gameScreen->setEnable(false);
        }
        if (getMainStage()->getChild("Options screen")) {
            m_optionsScreen->setVisible(false);
            m_optionsScreen->setEnable(false);
        }
		m_menuScreen->updateLayout();
        m_menuScreen->setVisible(true);
    } else if (name == "Options screen") {
        if (getMainStage()->getChild("Game screen")) {
            m_gameScreen->setVisible(false);
            m_gameScreen->setEnable(false);
        }
        if (getMainStage()->getChild("Options screen")) {
            m_optionsScreen->setVisible(true);
            m_optionsScreen->setEnable(true);
			m_optionsScreen->updateLayout();
        }
        m_menuScreen->setVisible(false);
    } else if (name == "Game screen") {
        if (getMainStage()->getChild("Options screen")) {
            m_optionsScreen->setVisible(false);
            m_optionsScreen->setEnable(false);
        }
        m_menuScreen->setVisible(false);
    }
}

