#include "dethgame.h"

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

void DethGame::setFullscreen(SDL_Window* window, bool is_fullscreen)
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, (IsFullscreen && is_fullscreen) ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
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
    m_menuScreen = new MainMenu();
    getMainStage()->addChild(m_menuScreen);
    config.setMusicVolume(77);
    oxygine::log::messageln("volume=%d",config.getMusicVolume());
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
        m_menuScreen->setVisible(true);
    } else if (name == "Options screen") {
        if (getMainStage()->getChild("Game screen")) {
            m_gameScreen->setVisible(false);
            m_gameScreen->setEnable(false);
        }
        if (getMainStage()->getChild("Options screen")) {
            m_optionsScreen->setVisible(true);
            m_optionsScreen->setEnable(true);
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

