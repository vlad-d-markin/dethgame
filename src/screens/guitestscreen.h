#ifndef DETHGAME_GUITESTSCREEN_H
#define DETHGAME_GUITESTSCREEN_H

#include "basescreen.h"
#include "oxygine-framework.h"


DECLARE_SMART(GuiTestScreen, spGuiTestScreen);
class GuiTestScreen : public BaseScreen {
public:
    GuiTestScreen();
    virtual ~GuiTestScreen();

};

#endif //DETHGAME_GUITESTSCREEN_H
