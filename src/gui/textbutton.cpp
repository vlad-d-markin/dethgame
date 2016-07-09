#include "textbutton.h"

//using namespace Gui;


Gui::TextButton::TextButton(const std::string &text)
{
//    ResAnim * buttonBg = resManager->getResAnim("base_button_bg");
//    setSize(buttonBg->getSize());

//    setResAnim(buttonBg);

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
}