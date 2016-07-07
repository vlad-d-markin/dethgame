#include "textbutton.h"


TextButton::TextButton(Resources *resManager, const std::string &text)
{
    ResAnim * buttonBg = resManager->getResAnim("base_button_bg");
    setSize(buttonBg->getSize());

    setResAnim(buttonBg);

    spTextField title = new TextField();
    title->setSize(getSize());

    TextStyle style = title->getStyle();
//    style.font = resManager->getResFont("barbecue52")->getFont();
//    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    title->setStyle(style);

    title->setText(text);
    title->attachTo(this);


//    addEventListener()
}

TextButton::~TextButton()
{

}
