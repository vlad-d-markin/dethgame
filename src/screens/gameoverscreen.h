#ifndef GAMEOVERSCREEN_H
#define GAMEOVERSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

class GameOverScreen : public BaseScreen
{
public:
	GameOverScreen();
	~GameOverScreen();
    void setEnable(bool _enable);
	void updateLayout();
	void setMsg(const std::string & msg);

protected:
    void doUpdate(const UpdateState &us);
private:
    bool enable;
    Resources * m_resources;
	Gui::spTextLabel msg;
};
typedef ::oxygine::intrusive_ptr<GameOverScreen> spGameOverScreen;

#endif // GAMEOVERSCREEN_H
