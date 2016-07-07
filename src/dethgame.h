#ifndef DETHGAME_H
#define DETHGAME_H

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

    void preInit();
    void init();
    void update();
    void destroy();



};

#endif // DETHGAME_H
