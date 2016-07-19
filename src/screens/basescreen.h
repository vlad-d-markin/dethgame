#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "oxygine-framework.h"

using namespace  oxygine;

class BaseScreen : public Actor
{
private:
    bool m_debug_mode; //name of screen, dont use
    spTextField m_screenNameField; //debug
public:
    BaseScreen(bool debugging = false);
    void setDebugging(bool b);
    virtual void show();
};

typedef ::oxygine::intrusive_ptr<BaseScreen> spBaseScreen;

#endif // BASESCREEN_H
