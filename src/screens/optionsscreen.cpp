#include "optionsscreen.h"
#include "../dethgame.h"

OptionsScreen::OptionsScreen()
{
    setName("Options screen");

    // Add panels
    Gui::spPanel main_panel = new Gui::Panel();
    main_panel->attachTo(this);
    main_panel->setSize(400, 400);
    main_panel->setPosition(200, 200);

    Gui::spPanel music_volume_panel = new Gui::Panel();
    main_panel->addElement(music_volume_panel);
    music_volume_panel->setSize(400, 30);

    Gui::spPanel effects_volume_panel = new Gui::Panel();
    main_panel->addElement(effects_volume_panel);
    effects_volume_panel->setSize(400, 60);
    effects_volume_panel->setPosition(0, 60);

    Gui::spPanel fullscreen_panel = new Gui::Panel();
    main_panel->addElement(fullscreen_panel);
    fullscreen_panel->setSize(400, 30);
    fullscreen_panel->setPosition(0, 120);

    // Add buttons
    Gui::spTextLabel music_vol_label = new Gui::TextLabel();
    music_vol_label->setText("Music volume:");
    music_volume_panel->addElement(music_vol_label);
    music_vol_label->setPosition(10, 8);

    m_dec_music_vol = new Gui::TextButton("-");
    music_volume_panel->addElement(m_dec_music_vol);
    m_dec_music_vol->setSize(20, 20);
    m_dec_music_vol->setPosition(100, 4);
    m_dec_music_vol->setAction("dec_music_volume");
    m_dec_music_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    m_inc_music_vol = new Gui::TextButton("+");
    music_volume_panel->addElement(m_inc_music_vol);
    m_inc_music_vol->setSize(20, 20);
    m_inc_music_vol->setPosition(340, 4);
    m_inc_music_vol->setAction("inc_music_volume");
    m_inc_music_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    m_music_vol_bar = new Gui::Bar();
    m_music_vol_bar->setPosition(130, 4);
    m_music_vol_bar->setValue(DethGame::instance()->getConfiguration()->getMusicVolume());
    music_volume_panel->addElement(m_music_vol_bar);


    // Fullscreen
    Gui::spTextLabel fullscreen_label = new Gui::TextLabel();
    fullscreen_label->setText("Full screen:");
    fullscreen_panel->addElement(fullscreen_label);
    fullscreen_label->setPosition(10, 8);

    m_fullscreen_switch = new Gui::Switch(DethGame::instance()->getConfiguration()->getFullScreen());
    fullscreen_panel->addElement(m_fullscreen_switch);
    m_fullscreen_switch->setPosition(100, 4);
    m_fullscreen_switch->addEventListener(Gui::SwitchStateChangedEvent::EVENT,
                                          CLOSURE(this, &OptionsScreen::onFullscreenChanged));



    // For development
    main_panel->showBoundaries(true);
    music_volume_panel->showBoundaries(true);
    effects_volume_panel->showBoundaries(true);
    fullscreen_panel->showBoundaries(true);
}



void OptionsScreen::onButtonClicked(Event * e)
{
    Gui::ButtonClickedEvent * ev = reinterpret_cast<Gui::ButtonClickedEvent *> (e);

    if(ev->m_action == "inc_music_volume")
    {
        m_music_vol_bar->setValue(m_music_vol_bar->getValue() + 2);
        DethGame::instance()->getConfiguration()->setMusicVolume(m_music_vol_bar->getValue());
    }
    else if(ev->m_action == "dec_music_volume")
    {
        m_music_vol_bar->setValue(m_music_vol_bar->getValue() - 2);
        DethGame::instance()->getConfiguration()->setMusicVolume(m_music_vol_bar->getValue());
    }

    log::messageln("Options button clicked: %s", ev->m_action.c_str());
}


void OptionsScreen::onFullscreenChanged(Event *e)
{
    Gui::SwitchStateChangedEvent * ev = reinterpret_cast<Gui::SwitchStateChangedEvent *> (e);

    DethGame::instance()->getConfiguration()->setFullScreen(ev->state);
    DethGame::instance()->setFullscreen(core::getWindow(), ev->state);
}
