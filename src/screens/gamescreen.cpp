#include "gamescreen.h"
#include "../dethgame.h"
#include "../player.h"
#include <iostream>
#include "basescreen.h"
#include "../map.h"

using namespace oxygine;

GameScreen::GameScreen()
{
    setName("Game screen");
    setSize(DethGame::instance()->getMainStage()->getSize());

    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    Map* map = new Map();
    //map->drawMap(this);
    map->drawGround(this);
    // ...pers draw
    map->drawTop(this);
}

Resources* GameScreen::getResources()
{
    return m_resources;
}
