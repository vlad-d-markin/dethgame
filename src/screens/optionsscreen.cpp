#include "optionsscreen.h"
#include "../dethgame.h"

OptionsScreen::OptionsScreen()
{
    setName("Options screen");
    setEnable(true);
    // Add panels
    m_main_panel = new Gui::Panel();
    m_main_panel->attachTo(this);
    m_main_panel->setSize(400, 400);

    Gui::spTextLabel options_label = new Gui::TextLabel();
    options_label->setText("Options");
	TextStyle style = options_label->getTextStyle();
	style.fontSize = 40;
	m_resources = new Resources();
	m_resources->loadXML(DethGame::instance()->getGuiResPath());
	style.font = m_resources->getResFont("font")->getFont();
	options_label->setTextStyle(style);
	options_label->setAnchor(0.5, 0.5);
    options_label->setPosition(m_main_panel->getWidth() / 2 - options_label->getWidth() / 2, -20);
    m_main_panel->addElement(options_label);

	m_resources = new Resources();
	m_resources->loadXML(DethGame::instance()->getGuiResPath());

    // Add buttons
    addMusicVolPanel();
    // Fx volume
    addFxVolPanel();
    // Fullscreen
    addFullscreenPanel();

    // For development
//    m_main_panel->showBoundaries(true);
}

void OptionsScreen::updateLayout()
{
	int x, y;
	SDL_GetWindowSize(core::getWindow(), &x, &y);
	m_main_panel->setPosition(Vector2(x,y) / 2 - m_main_panel->getSize() / 2);
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
    else if(ev->m_action == "inc_fx_volume")
    {
        m_fx_vol_bar->setValue(m_fx_vol_bar->getValue() + 2);
        DethGame::instance()->getConfiguration()->setFxVolume(m_fx_vol_bar->getValue());
    }
    else if(ev->m_action == "dec_fx_volume")
    {
        m_fx_vol_bar->setValue(m_fx_vol_bar->getValue() - 2);
        DethGame::instance()->getConfiguration()->setFxVolume(m_fx_vol_bar->getValue());
    }
    log::messageln("Options button clicked: %s", ev->m_action.c_str());
}

void OptionsScreen::onFullscreenChanged(Event *e)
{
    Gui::SwitchStateChangedEvent * ev = reinterpret_cast<Gui::SwitchStateChangedEvent *> (e);

    DethGame::instance()->getConfiguration()->setFullScreen(ev->state);
    DethGame::instance()->setFullscreen(core::getWindow(), ev->state);
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

void OptionsScreen::addMusicVolPanel()
{
    Gui::spPanel music_volume_panel = new Gui::Panel();
    m_main_panel->addElement(music_volume_panel);
    music_volume_panel->setSize(400, 30);
    music_volume_panel->setPosition(0, 40);

    Gui::spTextLabel music_vol_label = new Gui::TextLabel();

	TextStyle style = music_vol_label->getTextStyle();
	style.font = m_resources->getResFont("font")->getFont();
	style.fontSize = 20;
	music_vol_label->setTextStyle(style);

    music_vol_label->setText("Music volume:");
    music_volume_panel->addElement(music_vol_label);
    music_vol_label->setPosition(-30, 0);

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
}

void OptionsScreen::addFxVolPanel()
{
    Gui::spPanel effects_volume_panel = new Gui::Panel();
    m_main_panel->addElement(effects_volume_panel);
    effects_volume_panel->setSize(400, 30);
    effects_volume_panel->setPosition(0, 90);

    Gui::spTextLabel fx_vol_label = new Gui::TextLabel();

	TextStyle style = fx_vol_label->getTextStyle();
	
	style.font = m_resources->getResFont("font")->getFont();
	style.fontSize = 20;
	fx_vol_label->setTextStyle(style);

    fx_vol_label->setText("Effects volume:");
    effects_volume_panel->addElement(fx_vol_label);
    fx_vol_label->setPosition(-30, 0);

    m_dec_fx_vol = new Gui::TextButton("-");
    effects_volume_panel->addElement(m_dec_fx_vol);
    m_dec_fx_vol->setSize(20, 20);
    m_dec_fx_vol->setPosition(100, 4);
    m_dec_fx_vol->setAction("dec_fx_volume");
    m_dec_fx_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    m_inc_fx_vol = new Gui::TextButton("+");
    effects_volume_panel->addElement(m_inc_fx_vol);
    m_inc_fx_vol->setSize(20, 20);
    m_inc_fx_vol->setPosition(340, 4);
    m_inc_fx_vol->setAction("inc_fx_volume");
    m_inc_fx_vol->addEventListener(Gui::ButtonClickedEvent::EVENT, CLOSURE(this, &OptionsScreen::onButtonClicked));

    m_fx_vol_bar = new Gui::Bar();
    m_fx_vol_bar->setPosition(130, 4);
    m_fx_vol_bar->setValue(DethGame::instance()->getConfiguration()->getFxVolume());
    effects_volume_panel->addElement(m_fx_vol_bar);
}

void OptionsScreen::addFullscreenPanel()
{
    Gui::spPanel fullscreen_panel = new Gui::Panel();
    m_main_panel->addElement(fullscreen_panel);
    fullscreen_panel->setSize(400, 30);
    fullscreen_panel->setPosition(0, 140);

    Gui::spTextLabel fullscreen_label = new Gui::TextLabel();

	TextStyle style = fullscreen_label->getTextStyle();
	style.font = m_resources->getResFont("font")->getFont();
	style.fontSize = 20;
	fullscreen_label->setTextStyle(style);

    fullscreen_label->setText("Full screen:");
    fullscreen_panel->addElement(fullscreen_label);
    fullscreen_label->setPosition(-30, 0);

    m_fullscreen_switch = new Gui::Switch(DethGame::instance()->getConfiguration()->getFullScreen());
    fullscreen_panel->addElement(m_fullscreen_switch);
    m_fullscreen_switch->setPosition(100, 4);
    m_fullscreen_switch->addEventListener(Gui::SwitchStateChangedEvent::EVENT,
                                          CLOSURE(this, &OptionsScreen::onFullscreenChanged));
}

OptionsScreen::~OptionsScreen()
{
	m_resources->free();
	delete m_resources;
}
