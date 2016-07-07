#include "mainmenu.h"
#include "../dethgame.h"

MainMenu::MainMenu()
{
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    // Background
    spSprite background = new Sprite();
    background->setResAnim(m_resources->getResAnim("main_menu_bg"));
    background->setSize(getSize());
    float scale_factor = getWidth() / m_resources->getResAnim("main_menu_bg")->getWidth();
    background->setScale(scale_factor);
    background->attachTo(this);


    spTextButton btn = new TextButton(m_resources, "NEW GAME");
    btn->attachTo(this);
}



MainMenu::~MainMenu()
{
    m_resources->free();
    delete m_resources;
}
