#ifndef DETHGAME_ZOMBIE_H
#define DETHGAME_ZOMBIE_H

#include "mob.h"
#include "oxygine-framework.h"

using namespace oxygine;

DECLARE_SMART(Zombie, spZombie)
class Zombie : public Mob
{
private:
    Resources resources;

    spTween m_current_tween;


public:
    Zombie();
    virtual ~Zombie();

protected:
    virtual void doUpdate(UpdateState& us);

    virtual void onDie();


};


#endif //DETHGAME_ZOMBIE_H
