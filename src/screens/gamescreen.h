#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "basescreen.h"
#include "../gui/gui.h"
#include "../resetable.h"

using namespace oxygine;

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
	void setBananasOnMap(int bananas);
	void setBananas(int bananas);
    void rebuildWorld();

private:
    Resources * m_resources;
    bool enable;
	Gui::spBar hp_bar;
	Gui::spBar bananaCounter;
	int bananasOnMap;
    Resetable* gameworld;
protected:
    void doUpdate(const UpdateState &us);
};

typedef ::oxygine::intrusive_ptr<GameScreen> spGameScreen;
#endif // GAMESCREEN_H
