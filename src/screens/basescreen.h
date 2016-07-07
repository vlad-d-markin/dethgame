#ifndef BASESCREEN_H
#define BASESCREEN_H

#include "oxygine-framework.h"

using namespace  oxygine;

class BaseScreen : public Actor
{
public:
    BaseScreen();

    virtual void show();
};

typedef ::oxygine::intrusive_ptr<BaseScreen> spBaseScreen;

#endif // BASESCREEN_H
