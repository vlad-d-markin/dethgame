#include "guitestscreen.h"

#include "../gui/guielement.h"
#include "../gui/button.h"
#include "../gui/textbutton.h"
#include "../gui/bar.h"

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
    tbtn->setText("EXIT");

    Gui::spBar pbar = new Gui::Bar();
    pbar->setPosition(100, 200);
    pbar->attachTo(this);
    pbar->setSize(60, 500);

    pbar->setMaxValue(100);
    pbar->setValue(34);
}

GuiTestScreen::~GuiTestScreen()
{

}


