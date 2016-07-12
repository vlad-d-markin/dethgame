#include "dethgame.h"
#include "screens/mainmenu.h"
#include "screens/gamescreen.h"
#include "screens/optionsscreen.h"
#include "screens/guitestscreen.h"

using namespace oxygine;

DethGame * DethGame::instance()
{
    static DethGame game;
    return &game;
}


DethGame::DethGame():config(CONFIG)
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

void DethGame::setFullscreen(SDL_Window* window, bool is_fullscreen)
{
    Uint32 FullscreenFlag = SDL_WINDOW_FULLSCREEN;
    bool IsFullscreen = SDL_GetWindowFlags(window) & FullscreenFlag;
    SDL_SetWindowFullscreen(window, (IsFullscreen && is_fullscreen) ? 0 : FullscreenFlag);
    SDL_ShowCursor(IsFullscreen);
}


void DethGame::quit()
{
    core::requestQuit();
}


void DethGame::preInit()
{
    config.load();
}



void DethGame::init()
{
//    spMainMenu menu = new MainMenu();
//    getMainStage()->addChild(menu);
//    //spBaseScreen game = new BaseScreen();
//    //getMainStage()->addChild(game);
//    config.setMusicVolume(77);
//    oxygine::log::messageln("volume=%d",config.getMusicVolume());
//    setFullscreen(core::getWindow(), config.getFullScreen());

//    spMainMenu menu = new MainMenu();
//    spGuiTestScreen test = new GuiTestScreen();
//    getMainStage()->addChild(test);

    spOptionsScreen opt_screen = new OptionsScreen();
    opt_screen->setDebugging(true);
    getMainStage()->addChild(opt_screen);
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
    oxygine::log::messageln("destroy it bitch");
    config.save();
}


