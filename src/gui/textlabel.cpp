#include "textlabel.h"

using namespace oxygine;

Gui::TextLabel::TextLabel()
{
    setName("TextLabel");
    m_label = new TextField();
    m_label->attachTo(this);
}

Gui::TextLabel::~TextLabel()
{

}

void Gui::TextLabel::setText(const std::string &text)
{
    m_label->setText(text);
    setSize(m_label->getTextRect().getSize());
}

const std::string Gui::TextLabel::getText()
{
	return m_label->getText();
}

TextStyle Gui::TextLabel::getTextStyle()
{
    return m_label->getStyle();
}

void Gui::TextLabel::setTextStyle(TextStyle style)
{
    m_label->setStyle(style);
}

