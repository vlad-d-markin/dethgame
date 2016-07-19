#include "dethgame.h"
#include <iostream>

#define MAP_TMX_PATH "map.tmx"

using namespace oxygine;

DethGame * DethGame::instance()
{
    static DethGame game;
    return &game;
}

DethGame::DethGame():config(CONFIG) {}

spStage DethGame::getMainStage()
{
    return getStage();// oxygine function, returns main stage of the game
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
    SDL_GetCurrentDisplayMode(0, &mode);//take the size of our display

    SDL_SetWindowFullscreen(window, is_fullscreen ? old_flags | FullscreenFlag : old_flags & ~FullscreenFlag);

	if (is_fullscreen)
		SDL_SetWindowSize(window, mode.w, mode.h);
	else
		SDL_SetWindowSize(window, getMainStage()->getSize().x, getMainStage()->getSize().y);
//update screens (at the center)
	if (m_optionsScreen)
		m_optionsScreen->updateLayout();
	if (m_gameoverScreen)
		m_gameoverScreen->updateLayout();
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
    m_optionsScreen = new OptionsScreen();
    getMainStage()->addChild(m_optionsScreen);
    m_rulesScreen = new RulesScreen();
    getMainStage()->addChild(m_rulesScreen);
    m_gameScreen = new GameScreen();
    getMainStage()->addChild(m_gameScreen);
	m_gameoverScreen = new GameOverScreen();
	getMainStage()->addChild(m_gameoverScreen);

    setScreen("Menu");
}
//when u push the buttons
void DethGame::startGame(Event * event)
{
    setScreen("Game screen");
}

void DethGame::optionsScreen(Event *event)
{
    setScreen("Options screen");
}

void DethGame::rulesScreen(Event *event)
{
    setScreen("Rules screen");
}


void DethGame::update() {}

//exit
void DethGame::destroy()
{
    oxygine::log::messageln("destroy all. that's brutal");
    config.save();
}

void DethGame::setScreen(std::string name)
{
    if (name == "Menu") {
        m_gameScreen->rebuildWorld();
        m_gameScreen->setVisible(false);
        m_gameScreen->setEnable(false);

        m_rulesScreen->setVisible(false);
        m_rulesScreen->setEnable(false);

		m_gameoverScreen->setVisible(false);
		m_gameoverScreen->setEnable(false);

        m_optionsScreen->setVisible(false);
        m_optionsScreen->setEnable(false);

        m_menuScreen->updateLayout();
        m_menuScreen->setVisible(true);
    } else if (name == "Rules screen") {
        m_gameScreen->setVisible(false);
        m_gameScreen->setEnable(false);

        m_optionsScreen->setVisible(false);
        m_optionsScreen->setEnable(false);

		m_gameoverScreen->setVisible(false);
		m_gameoverScreen->setEnable(false);

        m_menuScreen->setVisible(false);

        m_rulesScreen->setVisible(true);
        m_rulesScreen->setEnable(true);
		m_rulesScreen->updateLayout();
    } else if (name == "Options screen") {
        m_gameScreen->setVisible(false);
        m_gameScreen->setEnable(false);

        m_rulesScreen->setVisible(false);
        m_rulesScreen->setEnable(false);

		m_gameoverScreen->setVisible(false);
		m_gameoverScreen->setEnable(false);

        m_menuScreen->setVisible(false);

        m_optionsScreen->setVisible(true);
        m_optionsScreen->setEnable(true);
        m_optionsScreen->updateLayout();
    } else if (name == "Game screen") {
        m_optionsScreen->setVisible(false);
        m_optionsScreen->setEnable(false);

        m_rulesScreen->setVisible(false);
        m_rulesScreen->setEnable(false);

		m_gameoverScreen->setVisible(false);
		m_gameoverScreen->setEnable(false);

        m_menuScreen->setVisible(false);

        m_gameScreen->rebuildWorld();
        m_gameScreen->setVisible(true);
        m_gameScreen->setEnable(true);
	} else if (name == "Game over screen") {
		m_optionsScreen->setVisible(false);
		m_optionsScreen->setEnable(false);

		m_rulesScreen->setVisible(false);
		m_rulesScreen->setEnable(false);

		m_menuScreen->setVisible(false);


        m_gameScreen->rebuildWorld();
		m_gameScreen->setVisible(false);
		m_gameScreen->setEnable(false);

		m_gameoverScreen->setVisible(true);
		m_gameoverScreen->setEnable(true);
	}
}

