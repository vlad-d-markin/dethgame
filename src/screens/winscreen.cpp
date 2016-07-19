#include "winscreen.h"
#include "../dethgame.h"
using namespace oxygine;

WinScreen::WinScreen()
{
    setName("Win screen");
    setEnable(true);

	winMsg = new Gui::TextLabel();
	TextStyle style = winMsg->getTextStyle();
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());
    style.font = m_resources->getResFont("font")->getFont();
	winMsg->setText("BLOODWIN!");
    style.fontSize = 70;
    style.hAlign = TextStyle::HALIGN_CENTER;
	winMsg->setTextStyle(style);
	winMsg->setAnchor(0.5, 0.5);
	updateLayout();
	winMsg->attachTo(this);
}

void WinScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);
	if (data[SDL_SCANCODE_ESCAPE] && enable)
		DethGame::instance()->setScreen("Menu");
}

void WinScreen::setEnable(bool _enable)
{
    enable = _enable;
}

void WinScreen::updateLayout()
{
	int x, y;
	SDL_GetWindowSize(core::getWindow(), &x, &y);
	winMsg->setPosition(x / 2 + winMsg->getWidth() / 2, y / 2);
}

WinScreen::~WinScreen() {}
