#include "textbutton.h"

Gui::TextButton::TextButton(const std::string &text)
{
    m_background = new ColorRectSprite();
    m_background->setSize(getSize());
    m_background->setColor(Color::DarkRed);
    m_background->attachTo(this);

    m_title = new TextField();
    m_title->setSize(getSize());
    TextStyle style = m_title->getStyle();
    style.color = Color::Black;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    m_title->setStyle(style);
    m_title->setText(text);
    m_title->attachTo(this);
	setSize(m_title->getTextRect().getSize() * 1.5);
}

Gui::TextButton::~TextButton() {}

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
    m_background->setColor(Color::Maroon);
}

void Gui::TextButton::onLeft()
{
    m_background->setColor(Color::DarkRed);
}

void Gui::TextButton::onPressed()
{
    m_background->setColor(Color::Firebrick);
}

void Gui::TextButton::onReleased()
{
    if(getOvered())
        m_background->setColor(Color::Maroon);
    else
        m_background->setColor(Color::DarkRed);
}
