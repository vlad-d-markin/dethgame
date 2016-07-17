#include "mainmenu.h"
#include "../dethgame.h"

#define GAP_SIZE 50

MainMenu::MainMenu()
{
    setName("Menu");
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());

    // Background
    background = new Sprite();
    background->setResAnim(m_resources->getResAnim("main_menu_bg"));
    background->attachTo(this);

    //Buttons
    //start button
    btn_start = new ImageButton(m_resources->getResAnim("start"));
	btn_start->addEventListener(TouchEvent::CLICK, CLOSURE(DethGame::instance(), &DethGame::startGame));
	btn_start->attachTo(this);
    //rules button
    btn_rules = new ImageButton(m_resources->getResAnim("rules"));
	btn_rules->attachTo(this);
    //options button
    btn_options = new ImageButton(m_resources->getResAnim("options"));
	btn_options->addEventListener(TouchEvent::CLICK, CLOSURE(DethGame::instance(), &DethGame::optionsScreen));
	btn_options->attachTo(this);
    //exit button
    btn_exit = new ImageButton(m_resources->getResAnim("exit"));
	btn_exit->attachTo(this);
	btn_exit->addEventListener(TouchEvent::CLICK, [](Event *){
        DethGame::instance()->quit();
    });

	updateLayout();

    // Tmp
    // btn->addClickListener([](){ DethGame::instance()->quit(); });
}


void MainMenu::updateLayout()
{
	int x, y;
	SDL_GetWindowSize(core::getWindow(), &x, &y);

	float scale_factor = x / m_resources->getResAnim("main_menu_bg")->getWidth();
	background->setScale(scale_factor);

	btn_start->setScale(scale_factor);
	btn_start->setPosition(x / 2 - btn_start->getWidth() / 2 * scale_factor, GAP_SIZE + y / 2);

	btn_rules->setScale(scale_factor);
	btn_rules->setPosition(x / 2 - btn_rules->getWidth() / 2 * scale_factor, GAP_SIZE + y / 2 + btn_rules->getHeight()*scale_factor);

	btn_options->setScale(scale_factor);
	btn_options->setPosition(x / 2 - btn_options->getWidth() / 2 * scale_factor, GAP_SIZE + y / 2 + 2 * btn_options->getHeight()*scale_factor);

	btn_exit->setScale(scale_factor);
	btn_exit->setPosition(x / 2 - btn_exit->getWidth() / 2 * scale_factor, GAP_SIZE + y / 2 + 3 * btn_exit->getHeight()*scale_factor);
}


MainMenu::~MainMenu()
{
    m_resources->free();
    delete m_resources;
}
