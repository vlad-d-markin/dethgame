#include "dethgame.h"
#include "screens/mainmenu.h"
#include "screens/guitestscreen.h"

using namespace oxygine;

DethGame * DethGame::instance()
{
    static DethGame game;
    return &game;
}


DethGame::DethGame()
{

}


spStage DethGame::getMainStage()
{
    return getStage();
}

std::string DethGame::getGuiResPath()
{
    return "gui.xml";
}



void DethGame::quit()
{
    core::requestQuit();
}


void DethGame::preInit()
{

}



void DethGame::init()
{
//    spMainMenu menu = new MainMenu();
    spGuiTestScreen test = new GuiTestScreen();
    getMainStage()->addChild(test);
}



void DethGame::update()
{

}


void DethGame::destroy()
{

}


