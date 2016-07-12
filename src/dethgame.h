#ifndef DETHGAME_H
#define DETHGAME_H

#include <string>
#include "oxygine-framework.h"

#include "screens/basescreen.h"


class DethGame
{
private:
    DethGame();
    DethGame(const DethGame&){}
    DethGame& operator=(const DethGame&){}

public:
    static DethGame * instance();

    oxygine::spStage getMainStage();
    std::string getGuiResPath();
    std::string getTileResPath();
    std::string getMapTmxPath();

    void preInit();
    void init();
    void update();
    void destroy();

    void startGame(Event *event);


};

#endif // DETHGAME_H
