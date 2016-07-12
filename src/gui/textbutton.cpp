#include "textbutton.h"

//using namespace Gui;


Gui::TextButton::TextButton(const std::string &text)
{
//    ResAnim * buttonBg = resManager->getResAnim("base_button_bg");
//    setSize(buttonBg->getSize());

//    setResAnim(buttonBg);

    m_background = new ColorRectSprite();
    m_background->setSize(getSize());
    m_background->setColor(Color::DarkGreen);
    m_background->attachTo(this);

    m_title = new TextField();
    m_title->setSize(getSize());
    TextStyle style = m_title->getStyle();
//    style.font = resManager->getResFont("barbecue52")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    m_title->setStyle(style);

    m_title->setText(text);
    m_title->attachTo(this);

    setSize(m_title->getTextRect().getSize() * 1.5);
}

Gui::TextButton::~TextButton()
{

}

void Gui::TextButton::setText(const std::string &text)
{
    m_title->setText(text);
}




void Gui::TextButton::onSizeChanged(const Vector2 &size)
{
    m_title->setSize(size);
    m_background->setSize(size);
}


void Gui::TextButton::onOvered()
{
    m_background->setColor(Color::Green);
}

void Gui::TextButton::onLeft()
{
    m_background->setColor(Color::DarkGreen);
}

void Gui::TextButton::onPressed()
{
    m_background->setColor(Color::Olive);
}

void Gui::TextButton::onReleased()
{
    if(getOvered())
        m_background->setColor(Color::Green);
    else
        m_background->setColor(Color::DarkGreen);
}
