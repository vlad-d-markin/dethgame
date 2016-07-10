#include "guitestscreen.h"

#include <functional>

#include "../gui/gui.h"

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
//    tbtn->setVisible(false);
    tbtn->setAction("inc");
    tbtn->addEventListener(Gui::ButtonClickedEvent::EVENT, [](::oxygine::Event * e){
        Gui::ButtonClickedEvent * ev = reinterpret_cast<Gui::ButtonClickedEvent *> (e);
        log::messageln("btn click listener action: %s", ev->m_action.c_str());
    });


    Gui::spBar pbar = new Gui::Bar();
    pbar->setPosition(125, 200);
    pbar->attachTo(this);
//    pbar->setSize(60, 500); // Doesn't work

    pbar->setMaxValue(100);
    pbar->setValue(34);

    Gui::spTextButton inc_btn = new Gui::TextButton();
    inc_btn->setText("+");
    inc_btn->attachTo(this);
    inc_btn->setSize(20, 20);
    inc_btn->setPosition(330, 200);
    inc_btn->addEventListener(Gui::ButtonClickedEvent::EVENT, [pbar](::oxygine::Event * e){
        pbar->setValue(pbar->getValue() + 2);
    });

    Gui::spTextButton dec_btn = new Gui::TextButton();
    dec_btn->setText("-");
    dec_btn->attachTo(this);
    dec_btn->setSize(20, 20);
    dec_btn->setPosition(100, 200);
    dec_btn->addEventListener(Gui::ButtonClickedEvent::EVENT, [pbar](::oxygine::Event * e){
        pbar->setValue(pbar->getValue() - 2);
    });


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
//    panel->setVisible(false);

    Gui::spTextLabel lbl = new Gui::TextLabel();
    lbl->setText("This is a text label");
    lbl->setPosition(10, 50);
    panel->addElement(lbl);
    lbl->showBoundaries(true);

    Gui::spSwitch swtch = new Gui::Switch(false);
    panel->addElement(swtch);
    swtch->setPosition(10, 100);
    swtch->addEventListener(Gui::SwitchStateChangedEvent::EVENT, [lbl](::oxygine::Event * e){
        Gui::SwitchStateChangedEvent * ev = reinterpret_cast<Gui::SwitchStateChangedEvent *> (e);
        if(ev->state) {
            lbl->setText("Enabled");
        }
        else {
            lbl->setText("Disabled");
        }
    });

}

GuiTestScreen::~GuiTestScreen()
{

}


