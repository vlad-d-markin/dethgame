#include "bar.h"

#define BAR_PADDING 3;


Gui::Bar::Bar(double maxvalue)
{
    m_maxvalue = maxvalue;
    m_value = 0;

    setName("BasicProgressBar");
    setSize(200, 20);

    m_background = new ColorRectSprite();
    m_background->attachTo(this);
    m_background->setColor(Color::Green);

    m_bar = new ColorRectSprite();
    m_bar->setColor(Color::Lime);
    m_bar->attachTo(m_background);

    m_title = new TextField();
    TextStyle style = m_title->getStyle();
//    style.font = resManager->getResFont("barbecue52")->getFont();
    style.color = Color::White;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    m_title->setStyle(style);
    m_title->attachTo(this);


    updateSizes(getSize());
    updateText();
}

Gui::Bar::~Bar() { }

void Gui::Bar::setValue(double value)
{
    if(value < 0 || value > m_maxvalue)
        return;

    m_value = value;
    if(m_maxvalue > 0) {
        m_bar->setWidth((float) m_value / m_maxvalue * (m_background->getWidth() - 6));
        updateText();
    }
}

double Gui::Bar::getValue()
{
    return m_value;
}

void Gui::Bar::setMaxValue(double maxvalue)
{
    if(maxvalue < 0)
        return;

    m_maxvalue = maxvalue;
}

double Gui::Bar::getMaxValue()
{
    return m_maxvalue;
}



void Gui::Bar::updateText()
{
    m_title->setText(std::to_string((int) m_value) + "/" + std::to_string((int) m_maxvalue));
}

void Gui::Bar::updateSizes(const Vector2 &basesize)
{
    m_background->setSize(basesize);

    m_bar->setHeight(basesize.y - 6);
    m_bar->setWidth(0);
    if(m_maxvalue > 0) {
        m_bar->setWidth((float) m_value / m_maxvalue * m_background->getWidth() - 6);
    }
    m_bar->setPosition(3, 3);

    m_title->setSize(basesize);
//    m_title->setPosition(0, 0);
}

void Gui::Bar::onSizeChanged(const Vector2 &size)
{
//    updateSizes(size);
}