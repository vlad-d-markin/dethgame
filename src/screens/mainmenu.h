#ifndef MAINMENU_H
#define MAINMENU_H

#include "basescreen.h"
#include "oxygine-framework.h"

//#include "../gui/textbutton.h"
#include "../gui/imagebutton.h"

class MainMenu : public BaseScreen
{
private:
    Resources * m_resources;
public:
    MainMenu();
    virtual ~MainMenu();
};

typedef ::oxygine::intrusive_ptr<MainMenu> spMainMenu;

#endif // MAINMENU_H
