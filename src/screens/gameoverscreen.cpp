#include "gameoverscreen.h"
#include "../dethgame.h"
using namespace oxygine;

GameOverScreen::GameOverScreen()
{
    setName("Game over screen");
    setEnable(true);

	msg = new Gui::TextLabel();
	nathanPic = new Sprite();
	TextStyle style = msg->getTextStyle();
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());
    style.font = m_resources->getResFont("font")->getFont();
    style.fontSize = 70;
    style.hAlign = TextStyle::HALIGN_CENTER;
	msg->setTextStyle(style);
	msg->setAnchor(0.5, 0.5);
	nathanPic->setResAnim(m_resources->getResAnim("dead"));
	msg->setText("YOU DEAD!");	
	nathanPic->setAnchor(0.5, 0.5);
	updateLayout();
	nathanPic->attachTo(this);
	msg->attachTo(this);
}


void GameOverScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

	if ((data[SDL_SCANCODE_ESCAPE] || data[SDL_SCANCODE_RETURN]) && enable)
		DethGame::instance()->setScreen("Menu");

    if (DethGame::instance()->isWin == true) {
		nathanPic->setResAnim(m_resources->getResAnim("win"));
		msg->setText("BLOODWIN!");
    } else if (msg->getText() == "BLOODWIN!") {
		nathanPic->setResAnim(m_resources->getResAnim("dead"));
		msg->setText("YOU DEAD!");
	}
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
	nathanPic->setPosition(x / 2, (y - nathanPic->getHeight() - msg->getHeight() - 20) / 2 );
}

void GameOverScreen::setMsg(const std::string & _msg)
{
	msg->setText(_msg);
}

GameOverScreen::~GameOverScreen() {}
