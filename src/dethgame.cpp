#include "dethgame.h"
#include "screens/mainmenu.h"

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



void DethGame::preInit()
{

}



void DethGame::init()
{
    spMainMenu menu = new MainMenu();
    getMainStage()->addChild(menu);
}



void DethGame::update()
{

}


void DethGame::destroy()
{

}


