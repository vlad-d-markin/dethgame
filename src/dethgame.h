#ifndef DETHGAME_H
#define DETHGAME_H

#include <string>
#include "oxygine-framework.h"
#include "configuration.h"
#include "screens/basescreen.h"
#include "screens/mainmenu.h"
#include "screens/gamescreen.h"
#include "screens/optionsscreen.h"
#include "screens/rulesscreen.h"
#include "screens/gameoverscreen.h"

#define CONFIG "dethconfig.json"

class DethGame
{
private:
    DethGame();
    DethGame(const DethGame&):config(CONFIG){}
    DethGame& operator=(const DethGame&){}
    Configuration config;
    spMainMenu m_menuScreen;
    spGameScreen m_gameScreen;
    spOptionsScreen m_optionsScreen;
    spRulesScreen m_rulesScreen;
	spGameOverScreen m_gameoverScreen;

public:
    static DethGame * instance();
	bool isWin;
    oxygine::spStage getMainStage();
    std::string getGuiResPath();
    std::string getTileResPath();
    std::string getBananaResPath();
    std::string getMapTmxPath();
    Configuration * getConfiguration();
	int getPlayerMaxHealth();

    void setFullscreen(SDL_Window* window, bool is_fullscreen);

    void preInit();
    void init();
    void update();
    void destroy();
    void setScreen(std::string name);

    void startGame(Event *event);
    void optionsScreen(Event *event);
    void rulesScreen(Event *event);
    void quit();

};

#endif // DETHGAME_H
