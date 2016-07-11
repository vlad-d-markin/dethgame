#ifndef DETHGAME_H
#define DETHGAME_H

#include <string>
#include "oxygine-framework.h"
#include "configuration.h"
#include "screens/basescreen.h"

#define CONFIG "dethconfig.json"

class DethGame
{
private:
    DethGame();
    DethGame(const DethGame&):config(CONFIG){}
    DethGame& operator=(const DethGame&){}
    Configuration config;

public:
    static DethGame * instance();

    oxygine::spStage getMainStage();
    std::string getGuiResPath();
    std::string getTileResPath();

    void setFullscreen(SDL_Window* window, bool is_fullscreen);

    void preInit();
    void init();
    void update();
    void destroy();

    void startGame(Event *event);


};

#endif // DETHGAME_H
