#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

using namespace oxygine;


DECLARE_SMART(OptionsScreen, spOptionsScreen)
class OptionsScreen : public BaseScreen
{
private:
    Gui::spTextButton m_dec_music_vol;
    Gui::spTextButton m_inc_music_vol;
    Gui::spBar m_music_vol_bar;
    Gui::spSwitch m_fullscreen_switch;

public:
    OptionsScreen();

protected:
    void onButtonClicked(Event * e);
    void onFullscreenChanged(Event * e);
};

#endif // OPTIONSSCREEN_H
