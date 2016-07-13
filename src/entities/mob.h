#ifndef DETHGAME_MOB_H
#define DETHGAME_MOB_H

#include "oxygine-framework.h"
#include "entity.h"


DECLARE_SMART(Mob, spMob)
class Mob : public Entity {
private:
    int m_health;
    bool m_dead;

public:

    virtual void doUpdate(const UpdateState& us);

};


#endif //DETHGAME_MOB_H
