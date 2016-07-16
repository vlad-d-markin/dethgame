#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "basescreen.h"
#include "../gui/gui.h"

class GameScreen : public BaseScreen
{
public:
    GameScreen();
	~GameScreen();
    Resources* getResources();
    void setEnable(bool _enable);
	void setBarsPos(Vector2 pos);
	Vector2 getHpBarSize();
	void setHp(int hp);
	int getHp();
	void setBananas(int bananas);

private:
    Resources * m_resources;
    bool enable;
	Gui::spBar hp_bar;
	Gui::spBar bananaCounter;
protected:
    void doUpdate(const UpdateState &us);
};

typedef ::oxygine::intrusive_ptr<GameScreen> spGameScreen;

#endif // GAMESCREEN_H
