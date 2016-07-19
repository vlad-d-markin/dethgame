#include "bar.h"
#include "../dethgame.h"

#define BAR_PADDING 3;
using namespace oxygine;

Gui::Bar::Bar(double maxvalue)
{
	m_resources = new Resources;
	m_resources->loadXML(DethGame::instance()->getGuiResPath());

    m_maxvalue = maxvalue;
    m_value = 0;

    setName("BasicProgressBar");
    setSize(170, 11);

	m_background = new Sprite();
	m_background->attachTo(this);
	m_background->setResAnim(m_resources->getResAnim("pg"));
	m_background->setAnchor(0, 1);
						   
    m_bar = new ColorRectSprite();
	m_bar->setColor(Color::Black);
    m_bar->attachTo(m_background);

    m_title = new TextField();
    TextStyle style = m_title->getStyle();
    style.color = Color::Firebrick;
    style.vAlign = TextStyle::VALIGN_MIDDLE;
    style.hAlign = TextStyle::HALIGN_CENTER;
    m_title->setStyle(style);
	m_title->setPosition(5, -12);
    m_title->attachTo(this);

    updateSizes(getSize());
    updateText();
}

Gui::Bar::~Bar() 
{
	m_resources->free();
	delete m_resources;
}

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
        m_bar->setWidth((float) m_value / m_maxvalue * (m_background->getWidth() - 6));
    }
	m_bar->setPosition(15, m_background->getHeight() * 2);
    m_title->setSize(basesize);
}

void Gui::Bar::onSizeChanged(const Vector2 &size)
{
//    updateSizes(size);
}

void Gui::Bar::setTextStyle(TextStyle style)
{
	m_title->setStyle(style);
}

TextStyle Gui::Bar::getTextStyle()
{
	return m_title->getStyle();
}

void Gui::Bar::setTextPosition(Vector2 pos)
{
	m_title->setPosition(pos);
}

Vector2 Gui::Bar::getTextPosition()
{
	return m_title->getPosition();
}

void Gui::Bar::removeBackground()
{
	m_bar->detach();
	m_background->detach();
}
