#ifndef DETHGAME_TESTMOB_H
#define DETHGAME_TESTMOB_H

#include "oxygine-framework.h"
#include "mob.h"


DECLARE_SMART(TestMob, spTestMob)
class TestMob : public Mob {
private:
    spColorRectSprite m_kaban;

public:
    TestMob();


protected:
    virtual void doUpdate(const UpdateState& us);

};


#endif //DETHGAME_TESTMOB_H
