#include "panel.h"

Gui::Panel::Panel() {}
Gui::Panel::~Panel() {}

void Gui::Panel::addElement(spElement element)
{
    addChild(element);
}

void Gui::Panel::removeElement(spElement element)
{
    removeChild(element);
}
