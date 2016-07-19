#include "switch.h"

Gui::Switch::Switch(bool state)
{
    m_state = state;

    m_background = new ColorRectSprite();
    m_background->setSize(20, 20);
    m_background->setColor(Color::DarkRed);
    m_background->attachTo(this);

    m_indicator = new ColorRectSprite();
    m_indicator->setSize(16, 16);
    m_indicator->setPosition(2, 2);
    m_indicator->attachTo(m_background);

    updateIndicator();
}

void Gui::Switch::toggle()
{
    m_state = !m_state;
    SwitchStateChangedEvent stateChangedEvent(m_state);
    dispatchEvent(&stateChangedEvent);
    updateIndicator();
}

void Gui::Switch::updateIndicator()
{
    if(m_state)
        m_indicator->setColor(Color::Firebrick);
    else
        m_indicator->setColor(Color::Maroon);
}

void Gui::Switch::onClicked(Event *event)
{
    toggle();
}

void Gui::Switch::onOvered()
{
    m_background->setColor(Color::Maroon);
}

void Gui::Switch::onLeft()
{
    m_background->setColor(Color::DarkRed);
}
