#include "zombie.h"

#define IDLE_TWEEN addTween(TweenAnim(m_idle_anim), 1600, -1, true)
#define DIE_TWEEN addTween(TweenAnim(m_die_anim), 800)

#define PUNCH_SOUTH_TWEEN addTween(TweenAnim(m_attack_south), 600)

Zombie::Zombie() : Mob()
{
    resources.loadXML("zombie.xml");

    m_walk_south_anim = resources.getResAnim("zombie_walk_south");
    m_walk_north_anim = resources.getResAnim("zombie_walk_south");
    m_walk_east_anim = resources.getResAnim("zombie_walk_south");
    m_walk_west_anim = resources.getResAnim("zombie_walk_south");

    m_attack_south = resources.getResAnim("zombie_attack_south");

    m_die_anim = resources.getResAnim("zombie_die");
    m_idle_anim = resources.getResAnim("zombie_idle");

    m_current_tween = IDLE_TWEEN;
    m_state = IDLE;
}


Zombie::~Zombie()
{
    resources.free();
}


void Zombie::punch(Direction dir)
{
    switch (dir){
        case SOUTH: {
            m_state = PUNCHING_SOUTH;
            removeTween(m_current_tween);
            m_current_tween = PUNCH_SOUTH_TWEEN;
            m_current_tween->setDoneCallback(CLOSURE(this, &Zombie::onPunchFinished));

            m_attack_area.setPosition(getX() - m_attack_area.getWidth() / 2, getY() + getHeight());
            m_attack_area.setSize(80, 80);
            ZombiePunchEvent punchEvent(m_attack_area);
            dispatchEvent(&punchEvent);
        }
            break;

        default:

            break;
    }
}


void Zombie::doUpdate(UpdateState &us)
{
    Mob::doUpdate(us);
}


void Zombie::onDie()
{
    removeTween(m_current_tween);
    m_current_tween = DIE_TWEEN;
}



void Zombie::onPunchFinished(Event *e)
{
    removeTween(m_current_tween);
    m_current_tween = IDLE_TWEEN;
    m_state = IDLE;
}