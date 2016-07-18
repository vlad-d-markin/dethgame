#include "gameoverscreen.h"
#include "../dethgame.h"
using namespace oxygine;

GameOverScreen::GameOverScreen()
{
    setName("Game over screen");
    setEnable(true);

	msg = new Gui::TextLabel();
	TextStyle style = msg->getTextStyle();
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());
    style.font = m_resources->getResFont("font")->getFont();
    style.fontSize = 70;
    style.hAlign = TextStyle::HALIGN_CENTER;
	msg->setTextStyle(style);
	msg->setAnchor(0.5, 0.5);
	msg->setText("YOU DEAD!");
	updateLayout();
	msg->attachTo(this);
}

void GameOverScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

	if (data[SDL_SCANCODE_ESCAPE] && enable)
		DethGame::instance()->setScreen("Menu");
		//DethGame::instance()->quit();

	if (DethGame::instance()->isWin == true)
		msg->setText("BLOODWIN!");
	else if (msg->getText() == "BLOODWIN!")
		msg->setText("YOU DEAD!");
}

void GameOverScreen::setEnable(bool _enable)
{
    enable = _enable;
}

void GameOverScreen::updateLayout()
{
	int x, y;
	SDL_GetWindowSize(core::getWindow(), &x, &y);
	msg->setPosition(x / 2 + msg->getWidth() / 2, y / 2);
}

void GameOverScreen::setMsg(const std::string & _msg)
{
	msg->setText(_msg);
}

GameOverScreen::~GameOverScreen()
{


}
