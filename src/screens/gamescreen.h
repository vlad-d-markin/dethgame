#ifndef GAMESCREEN_H
#define GAMESCREEN_H
#include "basescreen.h"
#include "../gui/gui.h"
#include "../resetable.h"
//#include "../player.h"

using namespace oxygine;

class GamePauseEvent : public Event
{
public:
    enum { EVENT = eventID('E', 'g', 'P', 'r') };
    bool pause;
    GamePauseEvent(bool ps) : Event(EVENT), pause(ps) {}
};

class GameScreen : public BaseScreen
{
public:
    GameScreen();
	~GameScreen();
    void rebuildWorld();
    Resources* getResources();
    void setEnable(bool _enable);
	void setBarsPos(Vector2 pos);
	Vector2 getHpBarSize();
	void setHp(int hp);
	int getHp();
	void setBananasOnMap(int bananas);
	void setBananas(int bananas);
	int getBananas();

    void setPauseText();
    void setTextPausePosition(Vector2 position);
    void turnPauseTextOn();
    void turnPauseTextOff();

private:
    Clock * m_clock_gamescreen;
    Resources * m_resources;
    Resources * m_pause_resources;
    Gui::spTextLabel pause_label;

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
