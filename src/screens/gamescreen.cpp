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

    World* world = new World(this);
    world->attachTo(this);
    gameworld = world;

	hp_bar = new Gui::Bar();
	hp_bar->setMaxValue(DethGame::instance()->getPlayerMaxHealth());
	hp_bar->setValue(DethGame::instance()->getPlayerMaxHealth());
	TextStyle style = hp_bar->getTextStyle();
	style.color = Color::Silver;
	hp_bar->setTextStyle(style);
	hp_bar->setTextPosition(Vector2(5, 7));
	hp_bar->attachTo(this);

	bananaCounter = new Gui::Bar();
	bananaCounter->setMaxValue(bananasOnMap);
	bananaCounter->setValue(0);
	bananaCounter->removeBackground();
	style.color = Color::Yellow;
	bananaCounter->setTextStyle(style);
	bananaCounter->attachTo(this);
    setPauseText();
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

void GameScreen::setBarsPos(Vector2 pos)
{
	hp_bar->setPosition(pos);
	bananaCounter->setPosition(pos);
}

Vector2 GameScreen::getHpBarSize()
{
	return hp_bar->getSize();
}

void GameScreen::setHp(int hp)
{
	hp_bar->setValue(hp);
}

int GameScreen::getHp()
{
	return hp_bar->getValue();
}

void GameScreen::setBananas(int bananas)
{
	bananaCounter->setValue(bananas);
	
	if (bananaCounter->getValue() == bananaCounter->getMaxValue())
	{
		DethGame::instance()->setScreen("Win screen");
	}
}

void GameScreen::setBananasOnMap(int bananas)
{
	bananasOnMap = bananas;
}

int GameScreen::getBananas()
{
	return bananaCounter->getValue();
}

void GameScreen::rebuildWorld()
{
    gameworld->reBuildWorld();
}

void GameScreen::setPauseText()
{
    pause_label = new Gui::TextLabel();
    pause_label->setText("PAUSE");
    TextStyle style = pause_label->getTextStyle();
    style.fontSize = 100;
    m_pause_resources = new Resources();
    m_pause_resources->loadXML(DethGame::instance()->getGuiResPath());
    style.font = m_pause_resources->getResFont("font")->getFont();
    pause_label->setTextStyle(style);
    pause_label->setAnchor(0.5, 0.5);
    pause_label->attachTo(this);
    pause_label->setVisible(false);
}

GameScreen::~GameScreen()
{
	m_resources->free();
	delete m_resources;
}
