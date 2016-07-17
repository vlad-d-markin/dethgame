#include "rulesscreen.h"
#include "../dethgame.h"
using namespace oxygine;
RulesScreen::RulesScreen()
{
    setName("Rules screen");
    setEnable(true);

    Gui::spTextLabel rules_label = new Gui::TextLabel();
    rules_label->setText("Rules");
    TextStyle style = rules_label->getTextStyle();
    style.fontSize = 40;
    m_resources = new Resources();
    m_resources->loadXML(DethGame::instance()->getGuiResPath());
    style.font = m_resources->getResFont("font")->getFont();
    rules_label->setTextStyle(style);
    rules_label->setAnchor(0.5, 0.5);
    rules_label->setPosition(this->getWidth()/2 - rules_label->getWidth()/2, 50);
    rules_label->attachTo(this);
    Gui::spTextLabel rules = new Gui::TextLabel();
    rules->setText("There are no rules.\n\n\nBUT: To walk you should use W, A, S, D.\nTo attack - press Space.\n\nThat's all.\nBloodluck");
    style.fontSize = 35;
    style.hAlign = TextStyle::HALIGN_CENTER;
    rules->setTextStyle(style);
    rules->setAnchor(0.5,0.5);
    rules->setPosition(getWidth()/2 + rules->getWidth()/2, 180);
    rules->attachTo(this);
}


void RulesScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

    if (data[SDL_SCANCODE_ESCAPE] && enable)
        DethGame::instance()->setScreen("Menu");
}

void RulesScreen::setEnable(bool _enable)
{
    enable = _enable;
}

RulesScreen::~RulesScreen()
{


}
