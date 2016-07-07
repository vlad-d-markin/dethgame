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

    void preInit();
    void init();
    void update();
    void destroy();



};

#endif // DETHGAME_H
