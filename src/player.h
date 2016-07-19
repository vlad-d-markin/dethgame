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
    Resources * my_resources;
    ResAnim* resAnim;

    RectT<Vector2> m_collision_box;
    Vector2 mapSize;

    Vector2 pos;
    Vector2 position_spawn;
    float dirX;
    float dirY;
    float dirXOld;
    float dirYOld;
    bool movingOld;
    int VerticalAnimationDuration;
    int HorizontalAnimationDuration;

    //spColorRectSprite col_box;



    int weaponDamage;
    float intPunch;
    RectT<Vector2> attackArea;
    bool m_pause_mode;

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
    ResAnim* persAnimLeftAttack;
    ResAnim* persStandsUpAttack;
    ResAnim* persStandsDownAttack;
    ResAnim* persStandsRightAttack;
    ResAnim* persStandsLeftAttack;
    ResAnim* persAnimCurrent;
    ResAnim* persDeath;

    void rotate();
    bool moving;
    int getSign(const float number) const;
    spTween tween;
    Direction orientation;
    bool isPunching;
    bool isPunchingOld;

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

    int bananaCount;
    float dt_pause_press;

    void updatePunching(bool _isPunching);
    void onEvent(Event* ev);
    void onTweenDone(Event *event);

protected:
	void doUpdate(const UpdateState &us);
public:
    Player();
    Player(GameScreen *gs);
    void reset();

    RectT<Vector2> getCollisionBox();
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
    Vector2 getDirection();
    int getHP();

    void moveX(const float distance);
    void moveY(const float distance);
    void setMoving(const bool isMoving);
    Direction getOrientation();

    void punch();
    void takeDamage(int damage);
    void setNormalStateAnimation();

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
