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

    //Buttons
    spImageButton btn = new ImageButton(m_resources->getResAnim("start"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2);
    btn->attachTo(this);
    btn = new ImageButton(m_resources->getResAnim("rules"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2 + btn->getHeight()*scale_factor);
    btn->attachTo(this);
    btn = new ImageButton(m_resources->getResAnim("exit"));
    btn->setScale(scale_factor);
    btn->setPosition(getWidth()/2 - btn->getWidth()/2*scale_factor + 13, 50 + getHeight()/2 + 2*btn->getHeight()*scale_factor);
    btn->attachTo(this);

    // Tmp
    // btn->addClickListener([](){ DethGame::instance()->quit(); });
}



MainMenu::~MainMenu()
{
    m_resources->free();
    delete m_resources;
}
