#include "zombie.h"
#include "../player.h"
#include <iostream>

#define IDLE_TWEEN addTween(TweenAnim(m_idle_anim), 1600, -1, true)
#define DIE_TWEEN addTween(TweenAnim(m_die_anim), 800)

#define WALK_NORTH_TWEEN addTween(TweenAnim(m_walk_north_anim), 600)
#define WALK_SOUTH_TWEEN addTween(TweenAnim(m_walk_south_anim), 600)
#define WALK_EAST_TWEEN addTween(TweenAnim(m_walk_east_anim), 600)
#define WALK_WEST_TWEEN addTween(TweenAnim(m_walk_west_anim), 600)

#define PUNCH_SOUTH_TWEEN addTween(TweenAnim(m_attack_south), 600)
#define PUNCH_EAST_TWEEN addTween(TweenAnim(m_attack_east), 600)
#define PUNCH_WEST_TWEEN addTween(TweenAnim(m_attack_west), 600)
#define PUNCH_NORTH_TWEEN addTween(TweenAnim(m_attack_north), 600)

Zombie::Zombie(Vector2 spawn_pos) : Mob()
{
    resources.loadXML("zombie.xml");

    m_walk_south_anim = resources.getResAnim("zombie_walk_south");
    m_walk_north_anim = resources.getResAnim("zombie_walk_south");
    m_walk_east_anim = resources.getResAnim("zombie_walk_south");
    m_walk_west_anim = resources.getResAnim("zombie_walk_south");

    m_attack_south = resources.getResAnim("zombie_attack_south");
    m_attack_east = resources.getResAnim("zombie_attack_east");
    m_attack_west = resources.getResAnim("zombie_attack_west");
    m_attack_north = resources.getResAnim("zombie_attack_north");

    m_die_anim = resources.getResAnim("zombie_die");
    m_idle_anim = resources.getResAnim("zombie_idle");

    m_current_tween = IDLE_TWEEN;
    m_state = IDLE;

    m_pos_spawn = spawn_pos;
    setPosition(spawn_pos);

    m_health = HP;
    m_attack_damage = 50;//DAMAGE;

    m_agr_range = 300;
    m_attack_range = 65;
    m_attack_area.setSize(80,80);

    mob_box.setSize(Vector2(50,50));

    setAnchor(0.5, 0.5);
    brain = new MobBrain(m_agr_range, m_attack_range, m_pos_spawn);
}


Zombie::~Zombie()
{
    resources.free();
}


void Zombie::punch(Direction dir)
{
    if(m_state == DEAD)
        return;

    switch (dir){
        case down: {
            m_state = PUNCHING_SOUTH;
            removeTween(m_current_tween);
            m_current_tween = PUNCH_SOUTH_TWEEN;
            m_current_tween->setDoneCallback(CLOSURE(this, &Zombie::onPunchFinished));

            m_attack_area.setPosition(getX() - m_attack_area.getWidth() / 2, getY());

            ZombiePunchEvent punchEvent(m_attack_area, m_attack_damage);
            dispatchEvent(&punchEvent);
        }
            break;

        case right: {
            m_state = PUNCHING_EAST;
            removeTween(m_current_tween);
            m_current_tween = PUNCH_EAST_TWEEN;
            m_current_tween->setDoneCallback(CLOSURE(this, &Zombie::onPunchFinished));

            m_attack_area.setPosition(getX(), getY() - m_attack_area.getHeight() / 2);

            ZombiePunchEvent punchEvent(m_attack_area, m_attack_damage);
            dispatchEvent(&punchEvent);
        }
            break;

        case left: {
            m_state = PUNCHING_WEST;
            removeTween(m_current_tween);
            m_current_tween = PUNCH_WEST_TWEEN;
            m_current_tween->setDoneCallback(CLOSURE(this, &Zombie::onPunchFinished));

            m_attack_area.setPosition(getX() - m_attack_area.getWidth(), getY() - m_attack_area.getHeight() / 2);

            ZombiePunchEvent punchEvent(m_attack_area, m_attack_damage);
            dispatchEvent(&punchEvent);
        }
            break;


        case up: {
            m_state = PUNCHING_NORTH;
            removeTween(m_current_tween);
            m_current_tween = PUNCH_NORTH_TWEEN;
            m_current_tween->setDoneCallback(CLOSURE(this, &Zombie::onPunchFinished));

            m_attack_area.setPosition(getX() - m_attack_area.getWidth() / 2, getY() - m_attack_area.getHeight());

            ZombiePunchEvent punchEvent(m_attack_area, m_attack_damage);
            dispatchEvent(&punchEvent);
        }
            break;


        default:

            break;
    }
}



void Zombie::walk(Direction dir)
{
    if(m_state == DEAD)
        return;

    Vector2 step;

    switch (dir){
        case up:
            removeTween(m_current_tween);
            m_current_tween = WALK_NORTH_TWEEN;
            step.set(0, -64);
            break;

        case up_right:
            removeTween(m_current_tween);
            m_current_tween = WALK_EAST_TWEEN;
            step.set(64, -64);
            break;

        case up_left:
            removeTween(m_current_tween);
            m_current_tween = WALK_WEST_TWEEN;
            step.set(-64, -64);
            break;

        case left:
            removeTween(m_current_tween);
            m_current_tween = WALK_WEST_TWEEN;
            step.set(-64, 0);
            break;

        case right:
            removeTween(m_current_tween);
            m_current_tween = WALK_EAST_TWEEN;
            step.set(64, 0);
            break;

        case down:
            removeTween(m_current_tween);
            m_current_tween = WALK_SOUTH_TWEEN;
            step.set(0, 64);
            break;

        case down_left:
            removeTween(m_current_tween);
            m_current_tween = WALK_WEST_TWEEN;
            step.set(-64, 64);
            break;

        case down_right:
            removeTween(m_current_tween);
            m_current_tween = WALK_EAST_TWEEN;
            step.set(64, 64);
            break;

        default:
            step.set(0, 0);
            break;
    }

    m_currentMoveTween = addTween(Actor::TweenPosition(getPosition() + step), 600);
    m_current_tween->addDoneCallback(CLOSURE(this, &Zombie::onWalkComplete));
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



void Zombie::onWalkComplete(Event *e)
{
    removeTween(m_current_tween);
    removeTween(m_currentMoveTween);
    m_current_tween = IDLE_TWEEN;
    m_state = IDLE;
    ZombieArrived zombieArrived(getPosition());
    dispatchEvent(&zombieArrived);
}