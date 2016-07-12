#include "optionsscreen.h"
#include "../dethgame.h"

OptionsScreen::OptionsScreen()
{
    setName("Options screen");
    setEnable(true);
    // Add panels
    Gui::spPanel main_panel = new Gui::Panel();
    main_panel->attachTo(this);
    main_panel->setSize(400, 400);
    main_panel->setPosition(200, 200);

    Gui::spPanel music_volume_panel = new Gui::Panel();
    main_panel->addElement(music_volume_panel);
    music_volume_panel->setSize(400, 60);

    Gui::spPanel effects_volume_panel = new Gui::Panel();
    main_panel->addElement(effects_volume_panel);
    effects_volume_panel->setSize(400, 60);
    effects_volume_panel->setPosition(0, 60);

    Gui::spPanel fullscreen_panel = new Gui::Panel();
    main_panel->addElement(fullscreen_panel);
    fullscreen_panel->setSize(400, 60);
    fullscreen_panel->setPosition(0, 120);

    // Add buttons
    Gui::spTextButton dec_music_vol = new Gui::TextButton("-");
    music_volume_panel->addElement(dec_music_vol);
    dec_music_vol->setSize(20, 20);
    dec_music_vol->setAction("dec_music_volume");
    dec_music_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    Gui::spTextButton inc_music_vol = new Gui::TextButton("+");
    music_volume_panel->addElement(inc_music_vol);
    inc_music_vol->setSize(20, 20);
    inc_music_vol->setPosition(240, 0);
    inc_music_vol->setAction("inc_music_volume");
    inc_music_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    Gui::spBar music_vol_bar = new Gui::Bar();
    music_vol_bar->setPosition(30, 0);
    music_volume_panel->addElement(music_vol_bar);


    // For development
    main_panel->showBoundaries(true);
    music_volume_panel->showBoundaries(true);
    effects_volume_panel->showBoundaries(true);
    fullscreen_panel->showBoundaries(true);
}



void OptionsScreen::onButtonClicked(Event * e)
{
    Gui::ButtonClickedEvent * ev = reinterpret_cast<Gui::ButtonClickedEvent *> (e);

    log::messageln("Options button clicked: %s", ev->m_action.c_str());
}

void OptionsScreen::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

    if (data[SDL_SCANCODE_ESCAPE] && enable)
        DethGame::instance()->setScreen("Menu");
}

void OptionsScreen::setEnable(bool _enable)
{
    enable = _enable;
}
