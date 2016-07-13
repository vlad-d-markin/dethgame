#include "gamescreen.h"
#include "../dethgame.h"
#include <iostream>
#include "basescreen.h"
#include "../world.h"

using namespace oxygine;

GameScreen::GameScreen()
{
    setName("Game screen");
    setEnable(true);
    setSize(DethGame::instance()->getMainStage()->getSize());

    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    World* gameworld = new World(this);
    gameworld->draw();
    gameworld->attachTo(this);

}

void GameScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

    if (data[SDL_SCANCODE_ESCAPE] && enable)
        DethGame::instance()->setScreen("Menu");
}


Resources* GameScreen::getResources()
{
    return m_resources;
}

void GameScreen::setEnable(bool _enable)
{
    enable = _enable;
}
