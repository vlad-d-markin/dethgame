#ifndef MAINMENU_H
#define MAINMENU_H

#include "basescreen.h"
#include "oxygine-framework.h"

#include "../gui/textbutton.h"


class MainMenu : public BaseScreen
{
private:
    Resources * m_resources;

    spTextButton m_new_game_button;

public:
    MainMenu();
    virtual ~MainMenu();
};


typedef ::oxygine::intrusive_ptr<MainMenu> spMainMenu;


#endif // MAINMENU_H
