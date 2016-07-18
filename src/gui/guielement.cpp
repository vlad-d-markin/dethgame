#include "guielement.h"

using namespace oxygine;

Gui::Element::Element()
{
    m_boundaries = new ColorRectSprite();
    m_boundaries->setColor(Color(rand()));
    m_boundaries->attachTo(this);
    m_boundaries->setVisible(false);
    addClickListener(CLOSURE(this, &Element::onClicked));
}

Gui::Element::~Element() {}

void Gui::Element::showBoundaries(bool visible)
{
    m_boundaries->setVisible(visible);
}

void Gui::Element::onOvered()
{
    log::messageln("GUI Element %s overed.", getName().c_str());
}

void Gui::Element::onLeft()
{
    log::messageln("GUI Element %s left.", getName().c_str());
}

void Gui::Element::onPressed()
{
    log::messageln("GUI Element %s pressed.", getName().c_str());
}

void Gui::Element::onReleased()
{
    log::messageln("GUI Element %s released.", getName().c_str());
}

void Gui::Element::onClicked(Event * e)
{
    log::messageln("GUI Element %s clicked.", getName().c_str());
}

void Gui::Element::onSizeChanged(const Vector2 &size)
{
    log::messageln("GUI Element %s size changed.", getName().c_str());
}

void Gui::Element::updateStateOvered()
{
    Actor::updateStateOvered();
    if(getOvered())
        onOvered();
     else
        onLeft();
}

void Gui::Element::updateStatePressed()
{
    Actor::updateStatePressed();
    if(getPressed())
        onPressed();
    else
        onReleased();
}

void Gui::Element::sizeChanged(const Vector2 &size)
{
    Actor::sizeChanged(size);
    onSizeChanged(size);
    if(m_boundaries)
        m_boundaries->setSize(size);
}
