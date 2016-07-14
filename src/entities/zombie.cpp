#include "zombie.h"


Zombie::Zombie() : Mob()
{
    resources.loadXML("zombie.xml");

    ResAnim * wlk = resources.getResAnim("zombie_walk_south");

//    m_zombie_sprite = new Sprite();
//    m_zombie_sprite->attachTo(this);


//    setResAnim(wlk, 0, 3);
    m_current_tween = addTween(TweenAnim(wlk), 800, -1);

}


Zombie::~Zombie()
{
    resources.free();
}


void Zombie::doUpdate(UpdateState &us)
{
//    m_zombie_sprite->setPosition(getPosition())
    Mob::doUpdate(us);
}


void Zombie::onDie()
{
    removeTween(m_current_tween);
    addTween(TweenAnim(resources.getResAnim("zombie_die")), 800);
}