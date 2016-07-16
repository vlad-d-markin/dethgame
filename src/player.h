#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include <iostream>

using namespace oxygine;

class Player : public Sprite
{
    enum Direction {
        NORTH,
        SOUTH,
        EAST,
        WEST
    };
private: 
	Vector2 mapSize;
    Resources * my_resources;
    ResAnim* resAnim;
    Vector2 pos;
    float dirX;
    float dirY;
    RectT<Vector2> * rectangle;

    int weaponDamage;
    float intPunch;
    RectT<Vector2> attackArea;


    // что мы планировали использовать
    int healthPoints;
    int stamina;
    int healthRegenerationSpeed;
    int staminaRegenerationSpeed;
    int movementSpeed;
    int criticalHit;
    int accuracy;
    int hitResistance;
    int shotResistance;
    int hitEvasion;
    int shotEvasion;
    int weaponHandlingSpeed;
    int Vnorm;

    // что мы используем на самом деле
    int bananaCount;

protected:
	void doUpdate(const UpdateState &us);
public:
    Player();
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
    Vector2 getDirection();
    RectT<Vector2> getCollisionBox();

    void setDirection(float dir_x, float dir_y);
    void moveX();
    void moveY();

    void punch(Direction dir);
    void takeDamage(int damage);

    RectT<Vector2> getRectPlayer();

    void addBanana();
};


class PlayerPunchEvent : public Event
{
public:
    enum { EVENT = eventID('P', 'p', 'E', 'N') };
    RectT<Vector2> attack_area;
    int damage;

    PlayerPunchEvent(RectT<Vector2> area, int dmg) : Event(EVENT), attack_area(area), damage(dmg) {}
};


typedef ::oxygine::intrusive_ptr<Player> spPlayer;

#endif // PLAYER_H
