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
	spSprite background;
	spImageButton btn_start;
	spImageButton btn_rules;
	spImageButton btn_options;
	spImageButton btn_exit;

public:
    MainMenu();
    virtual ~MainMenu();
	void updateLayout();
};

typedef ::oxygine::intrusive_ptr<MainMenu> spMainMenu;

#endif // MAINMENU_H
