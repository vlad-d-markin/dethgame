#include "mainmenu.h"
#include "../dethgame.h"

MainMenu::MainMenu()
{
    setName("Menu");
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    // Background
    spSprite background = new Sprite();
    background->setResAnim(m_resources->getResAnim("main_menu_bg"));
    background->setSize(getSize());
    float scale_factor = getWidth() / m_resources->getResAnim("main_menu_bg")->getWidth();
    background->setScale(scale_factor);
    background->attachTo(this);

    //Buttons
    spImageButton btn = new ImageButton(m_resources->getResAnim("start"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2);
    EventCallback cb = CLOSURE(DethGame::instance(),&DethGame::startGame);
    btn->addEventListener(TouchEvent::CLICK, cb);
    btn->attachTo(this);
    btn = new ImageButton(m_resources->getResAnim("rules"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2 + btn->getHeight()*scale_factor);
    btn->attachTo(this);
    btn = new ImageButton(m_resources->getResAnim("exit"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2 + 2*btn->getHeight()*scale_factor);
    btn->attachTo(this);
}



MainMenu::~MainMenu()
{
    m_resources->free();
    delete m_resources;
}