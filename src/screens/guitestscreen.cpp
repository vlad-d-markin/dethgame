#include "guitestscreen.h"

#include "../gui/guielement.h"
#include "../gui/button.h"
#include "../gui/textbutton.h"
#include "../gui/bar.h"
#include "../gui/panel.h"

GuiTestScreen::GuiTestScreen()
{
    setName("GuiTestScreen");
    //
    setDebugging(true);

    Gui::spElement el = new Gui::Element();
    el->attachTo(this);
    el->setSize(300, 30);
    el->showBoundaries(true);
    el->setName("Empty base element");
    el->setPosition(100, 100);

    Gui::spTextButton tbtn = new Gui::TextButton("Some text");
    tbtn->setSize(300, 30);
    tbtn->attachTo(this);
    tbtn->setName("Text button");
    tbtn->setPosition(100, 160);
    tbtn->setText("Text button");

    Gui::spBar pbar = new Gui::Bar();
    pbar->setPosition(100, 200);
    pbar->attachTo(this);
    pbar->setSize(60, 500);

    pbar->setMaxValue(100);
    pbar->setValue(34);

    Gui::spPanel panel = new Gui::Panel();
    panel->setSize(400, 300);
    panel->setPosition(500, 80);
    panel->showBoundaries(true);
    panel->attachTo(this);

    Gui::spBar pbar1 = new Gui::Bar();
    pbar1->setPosition(10, 10);
    pbar1->attachTo(this);
    pbar1->setSize(60, 500);

    pbar1->setMaxValue(1130);
    pbar1->setValue(562);
    panel->addElement(pbar1);
}

GuiTestScreen::~GuiTestScreen()
{

}


