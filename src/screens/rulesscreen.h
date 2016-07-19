#ifndef RULESSCREEN_H
#define RULESSCREEN_H

#include "../gui/gui.h"
#include "basescreen.h"
#include "oxygine-framework.h"

class RulesScreen : public BaseScreen
{
public:
    RulesScreen();
    ~RulesScreen();
    void setEnable(bool _enable);
	void updateLayout();
protected:
    void doUpdate(const UpdateState &us);
private:
    bool enable;
    Resources * m_resources;
	Gui::spTextLabel rules_label;
	Gui::spTextLabel rules;
};
typedef ::oxygine::intrusive_ptr<RulesScreen> spRulesScreen;

#endif // RULESSCREEN_H
