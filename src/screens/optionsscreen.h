#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

using namespace oxygine;


DECLARE_SMART(OptionsScreen, spOptionsScreen)
class OptionsScreen : public BaseScreen
{
public:
    OptionsScreen();

protected:
    void onButtonClicked(Event * e);
};

#endif // OPTIONSSCREEN_H
