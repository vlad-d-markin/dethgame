#include "gamescreen.h"
#include "../dethgame.h"
#include <iostream>
#include "basescreen.h"
#include "../world.h"

using namespace oxygine;

GameScreen::GameScreen()
{
    setName("Game screen");
    setSize(DethGame::instance()->getMainStage()->getSize());

    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    World* gameworld = new World(this);
    gameworld->draw();
    gameworld->attachTo(this);

}

Resources* GameScreen::getResources()
{
    return m_resources;
}
