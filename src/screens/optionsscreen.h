#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

using namespace oxygine;

class OptionsScreen : public BaseScreen
{
public:
    OptionsScreen();
    void setEnable(bool _enable);

protected:
    void onButtonClicked(Event * e);
    void doUpdate(const UpdateState &us);
private:
    bool enable;
};

typedef ::oxygine::intrusive_ptr<OptionsScreen> spOptionsScreen;
//DECLARE_SMART(OptionsScreen, spOptionsScreen)

#endif // OPTIONSSCREEN_H
