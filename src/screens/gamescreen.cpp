#include "gamescreen.h"
#include "../dethgame.h"
#include "../mySprite.h"
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
    map->attachToMap(this);

    /*// Background
    spSprite background = new Sprite();
    background->setResAnim(m_resources->getResAnim("main_menu_bg"));
    background->setSize(getSize());
    //background->attachTo(this);


    spMySprite sprite = new MySprite;
    sprite->setAnchor(0.5, 0.5);
    sprite->setResAnim(m_resources->getResAnim("skin"));
    sprite->attachTo(this);
    sprite->setPosition(getSize() / 2);

    //camera
    spActor camera = new Actor;
    camera->addChild(background);
    camera->addChild(sprite);
    camera->setAnchor(0.5, 0.5);
    getStage()->addChild(camera);*/
}
