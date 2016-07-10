#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "basescreen.h"

class GameScreen : public BaseScreen
{
public:
    GameScreen();
private:
    Resources * m_resources;
};

typedef ::oxygine::intrusive_ptr<GameScreen> spGameScreen;

#endif // GAMESCREEN_H
