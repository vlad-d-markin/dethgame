#ifndef PLAYER_H
#define PLAYER_H

#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "screens/gamescreen.h"
#include <iostream>
#include "direction.h"

using namespace oxygine;

class Player : public Sprite
{
private: 
    Vector2 mapSize;
    Resources * my_resources;
    ResAnim* resAnim;
    Vector2 pos;
    float dirX;
    float dirY;
    float dirXOld;
    float dirYOld;
    bool movingOld;
    int VerticalAnimationDuration;
    int HorizontalAnimationDuration;
    RectT<Vector2> * rectangle;

    int weaponDamage;
    float intPunch;
    RectT<Vector2> attackArea;

    GameScreen *gamescreen;
    ResAnim* persAnimUp;
    ResAnim* persAnimDown;
    ResAnim* persAnimRight;
    ResAnim* persStandsUp;
    ResAnim* persStandsDown;
    ResAnim* persStandsRight;
    ResAnim* persAnimUpAttack;
    ResAnim* persAnimDownAttack;
    ResAnim* persAnimRightAttack;
    ResAnim* persStandsUpAttack;
    ResAnim* persStandsDownAttack;
    ResAnim* persStandsRightAttack;
    ResAnim* persAnimCurrent;
    void rotate();
    bool moving;
    int getSign(const float number);
    spTween tween;
    Direction orientation;
    bool isPunching;
    bool isPunchingOld;

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
    Player(GameScreen *gs);
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
    Vector2 getDirection();
    RectT<Vector2> getCollisionBox();

    void moveX(const float distance);
    void moveY(const float distance);
    void setMoving(const bool isMoving);
    Direction getOrientation();

    void punch(Direction dir);
    void takeDamage(int damage);

    RectT<Vector2> getRectPlayer();

    void getBanana();
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
