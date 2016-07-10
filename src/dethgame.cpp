#include "dethgame.h"
#include "screens/mainmenu.h"
#include "screens/gamescreen.h"

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

std::string DethGame::getTileResPath()
{
    return "tile.xml";
}



void DethGame::preInit()
{

}



void DethGame::init()
{
    spMainMenu menu = new MainMenu();
    getMainStage()->addChild(menu);
    //spBaseScreen game = new BaseScreen();
    //getMainStage()->addChild(game);
}

void DethGame::startGame(Event * event)
{
//    getMainStage()->getChild("menu")->detach();
    spGameScreen game = new GameScreen();
//    getMainStage()->getFirstChild()->detach();
    getMainStage()->addChild(game);
    getMainStage()->getLastChild()->setVisible(false);
    //getMainStage()->getChild("Menu")->setVisible(true);

    //oxygine::log::messageln("%s",getMainStage()->getChildren(getMainStage()));
}


void DethGame::update()
{

}


void DethGame::destroy()
{

}


