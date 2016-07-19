#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

class WinScreen : public BaseScreen
{
public:
	WinScreen();
	~WinScreen();
    void setEnable(bool _enable);
	void updateLayout();
protected:
    void doUpdate(const UpdateState &us);
private:
    bool enable;
    Resources * m_resources;
	Gui::spTextLabel winMsg;
};
typedef ::oxygine::intrusive_ptr<WinScreen> spWinScreen;

#endif // WINSCREEN_H
