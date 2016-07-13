#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "basescreen.h"

class GameScreen : public BaseScreen
{
public:
    GameScreen();
    Resources* getResources();
    void setEnable(bool _enable);
private:
    Resources * m_resources;
    bool enable;
protected:
    void doUpdate(const UpdateState &us);
};

typedef ::oxygine::intrusive_ptr<GameScreen> spGameScreen;

#endif // GAMESCREEN_H
