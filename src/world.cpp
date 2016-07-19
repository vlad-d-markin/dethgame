#include "world.h"
#include "map.h"
#include "entities/zombie.h"
#include "banana.h"
#include <iostream>



World::World(GameScreen *gs)
{
    gamescreen = gs;
    m_pause_mode = false;

    m_clock_world = new Clock;
    this->setClock(m_clock_world);

    setMapLand();
    setZombies();
    setBananas();
    setPlayer();
    setMapTop();
}


void World::reBuildWorld()
{
    // put the hero in default positions with initial characteristics
    m_player->reset();
    gamescreen->setHp(m_player->getHP());

    setZombies();

    setBananas();
    gamescreen->setBananas(0);
}


void World::setZombies()
{
    // remove old zombies
    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++) {
        (*it).second->detach();
    }
    m_mobs.clear();

    // add new zombies in default positions
    std::vector<Position> zombie_pos = m_map->getPosZombie();
    for (int i=0; i<(zombie_pos.size()); i++) {
        spZombie zombie = new Zombie(Vector2(zombie_pos[i].x,zombie_pos[i].y), m_map);
        zombie->setName("zomb");
        zombie->attachTo(this);
        zombie->addEventListener(MobCorpseDecayedEvent::EVENT, CLOSURE(this, &World::corpseDecayed));
        zombie->addEventListener(ZombiePunchEvent::EVENT, CLOSURE(this, &World::zombieAttacks));
        m_mobs.insert(std::pair<int, spMob>(zombie->getObjectID(), zombie));
    }
}


void World::setBananas()
{
    // remove old bananas
    for(int i=0; i < m_bananas.size(); i++) {
        m_bananas[i].deleteBanana();
    }
    m_bananas.clear();

    // add new bananas in default positions
    std::vector<Vector2> pos_bananas = m_map->getPosBananas();
    for(int i=0; i < pos_bananas.size(); i++) {
        Banana banana(pos_bananas[i], gamescreen);
        m_bananas.push_back(banana);
    }
    gamescreen->setBananasOnMap(m_map->getPosBananas().size());
}


void World::setMapLand()
{
    m_map = new Map();
    m_map->drawGround(gamescreen);
}


void World::setMapTop()
{
    m_map->drawTop(gamescreen);
}

void World::setPlayer()
{
    m_player = new Player(gamescreen);
    m_player->setAnchor(0.5, 0.5);
    m_player->attachTo(gamescreen);
    m_player->setMapSize(m_map->getMapSize());
    m_player->addEventListener(PlayerPunchEvent::EVENT, CLOSURE(this, &World::onPlayerPunch));
    m_player->addEventListener(GamePauseEvent::EVENT, CLOSURE(this, &World::onPause));
}


void World::doUpdate(const UpdateState &us)
{
    Actor::doUpdate(us);

    // update collecting bananas
    checkBanana();

    // broadcasting position of the player to mobs
    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++) {
         (*it).second->setPosPlayer(m_player->getPosition());
    }

    // check the player movenent on collision with obstacles
    checkPlayerMovement();
}


void World::checkBanana()
{
   RectT<Vector2> player_box = m_player->getCollisionBox();

   for(std::vector<Banana>::iterator i = m_bananas.begin(); i!=m_bananas.end(); i++){
       if(player_box.isIntersecting((*i).getCollisionBox()) == true) {
           m_player->addBanana();
           (*i).deleteBanana();
           m_bananas.erase(i);
           break;
       }
   }
}


void World::checkPlayerMovement()
{
    if( m_player->getDirection() == Vector2(0,0) ) {
        m_player->setMoving(false);
        return;
    }

    int num_steps = 10;
    float step_speed_x = (m_player->getDirection().x) / num_steps;
    float step_speed_y = (m_player->getDirection().y) / num_steps;
    bool playerMoved = false;

    for(int i = 0; i < num_steps; i++)
    {
        if(step_speed_x != 0)
        {
            RectT<Vector2> new_rect_player_x(m_player->getPosition()+Vector2(step_speed_x, 0), m_player->getSize());
            if(m_map->isObstacle(new_rect_player_x) == false) {
                m_player->moveX(step_speed_x);
                playerMoved = true;
            }
        }

        if(step_speed_y != 0)
        {
            RectT<Vector2> new_rect_player_y(m_player->getPosition()+Vector2(0, step_speed_y), m_player->getSize());
            if(m_map->isObstacle(new_rect_player_y) == false) {
                m_player->moveY(step_speed_y);
                playerMoved = true;
            }
        }
    }
    m_player->setMoving(playerMoved);
}


void World::corpseDecayed(Event *event)
{
    log::messageln("Corpse decayed");

    MobCorpseDecayedEvent * ev = reinterpret_cast<MobCorpseDecayedEvent *>(event);

    removeChild(ev->mob);

    m_mobs.erase(ev->mob->getObjectID());
}


void World::zombieAttacks(Event *event)
{
    log::messageln("Zombie attacked");

    ZombiePunchEvent * ev = reinterpret_cast<ZombiePunchEvent *>(event);

    RectT<Vector2> attack_box;
    attack_box = ev->attack_area;

    RectT<Vector2> player_box = m_player->getRectPlayer();

    if (player_box.isIntersecting(attack_box)) {
        m_player->takeDamage(ev->damage);
        gamescreen->setHp(gamescreen->getHp() - ev->damage);
	}
}


void World::onPlayerPunch(Event * event)
{
    log::messageln("Player attacked");

    PlayerPunchEvent * ev = reinterpret_cast<PlayerPunchEvent *>(event);

    RectT<Vector2> attack_box;
    attack_box = ev->attack_area;

    for(auto it = m_mobs.begin(); it != m_mobs.end(); it++) {
        if(attack_box.isIntersecting((*it).second->getMobBox())) {
            (*it).second->getHit(ev->damage);
        }
    }
}


void World::onPause(Event* event)
{
    if(m_pause_mode == false) {
        m_clock_world->pause();
        m_pause_mode = true;
    } else {
        m_clock_world->resume();
        m_pause_mode = false;
    }
}
