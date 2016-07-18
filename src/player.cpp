#include "SDL.h"
#include "SDL_keyboard.h"
#include "Input.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "player.h"
#include "dethgame.h"
#include <iostream>

#define DT_PAUSE_PRESS 300

using namespace oxygine;

Player::Player(GameScreen *gs) : Sprite()
{
    gamescreen = gs;
    m_pause_mode = false;
    dt_pause_press = DT_PAUSE_PRESS;

    VerticalAnimationDuration = 450;
    HorizontalAnimationDuration = 700;

    persAnimUp = gamescreen->getResources()->getResAnim("skin_goes_up");
    persAnimDown = gamescreen->getResources()->getResAnim("skin_goes_down");
    persAnimRight = gamescreen->getResources()->getResAnim("skin_goes_right");
    persStandsUp = gamescreen->getResources()->getResAnim("skin_stands_up");
    persStandsDown = gamescreen->getResources()->getResAnim("skin_stands_down");
    persStandsRight = gamescreen->getResources()->getResAnim("skin_goes_right");

    persAnimUpAttack = gamescreen->getResources()->getResAnim("skin_goes_up_attack");
    persAnimDownAttack = gamescreen->getResources()->getResAnim("skin_goes_down_attack");
    persAnimRightAttack = gamescreen->getResources()->getResAnim("skin_goes_right_attack");
    persStandsUpAttack = gamescreen->getResources()->getResAnim("skin_stands_up_attack");
    persStandsDownAttack = gamescreen->getResources()->getResAnim("skin_stands_down_attack");
    persStandsRightAttack = gamescreen->getResources()->getResAnim("skin_stands_right_attack");
    persDeath = gamescreen->getResources()->getResAnim("skin_died");

    setResAnim(persStandsDown);
    isPunching = false;
    isPunchingOld = false;
    orientation = down;
    moving = false;
    movingOld = false;
    dirX = 0;
    dirY = 0;
    dirXOld = 0;
    dirYOld = 0;

    pos = Vector2(300, 300);
    position_spawn=pos;
    setPosition(position_spawn);
    //Vnorm = ???
    weaponDamage = 30;
    intPunch = 0;
    attackArea.setSize(80,80);

	healthPoints = DethGame::instance()->getPlayerMaxHealth();
    stamina = 300;
    healthRegenerationSpeed = Vnorm;
    staminaRegenerationSpeed = Vnorm;
    movementSpeed = Vnorm;
    //criticalHit = урон оружия;
    accuracy = 0.7;
    hitResistance = 0;
    shotResistance = 0;
    hitEvasion = 0.1;
    shotEvasion = 0.1;
    weaponHandlingSpeed = Vnorm;

    bananaCount = 0;
}

Vector2 Player::getDirection()
{
    return Vector2(dirX, dirY);
}

void Player::moveX(const float distance)
{
    pos.x += distance;
    setPosition(pos);
}

void Player::moveY(const float distance)
{
    pos.y += distance;
    setPosition(pos);
}

void Player::setMoving(const bool isMoving)
{
    movingOld = moving;
    moving = isMoving;
}

void Player::doUpdate(const UpdateState &us)
{
    const Uint8* data = SDL_GetKeyboardState(0);

    // check on pause press
    dt_pause_press += us.dt;
    if(dt_pause_press >= DT_PAUSE_PRESS) {
        if (data[SDL_SCANCODE_P]) {
            m_pause_mode = !m_pause_mode;
            dt_pause_press = 0;
            GamePauseEvent gamePauseEvent(true);
            dispatchEvent(&gamePauseEvent);
        }
    }

    if(m_pause_mode == true)
        return;

    intPunch += us.dt;

	//calculate speed using delta time
    float speed = 150.0f * (us.dt / 1000.0f);

    //Vector2 pos = getPosition();
    dirXOld = dirX;
    dirYOld = dirY;
    dirX = 0;
    dirY = 0;

    if (healthPoints > 0) {
        if (data[SDL_SCANCODE_A])
            dirX -= speed;
        if (data[SDL_SCANCODE_D])
            dirX += speed;
        if (data[SDL_SCANCODE_W])
            dirY -= speed;
        if (data[SDL_SCANCODE_S])
            dirY += speed;
        if (data[SDL_SCANCODE_SPACE]) {
            updatePunching(true);
            punch();
        }
    }

    //choose an appropriate animation
    if( getSign(dirX) != getSign(dirXOld)
        || ( getSign(dirX) == 0 && getSign(dirY) != getSign(dirYOld) )
        || getSign(moving) != getSign(movingOld)
        || isPunching != isPunchingOld )
    {
        //std::cerr << "X=" << dirX << " Xo=" << dirXOld << " Y=" << dirY << " Yo=" << dirYOld <<
        //            " M=" << moving << " Mo=" << movingOld << " P=" << isPunching << std::endl;
        rotate();
    }

	int x, y;
	SDL_GetWindowSize(core::getWindow(), &x, &y);
	Vector2 windowSize(x, y);
		
	Vector2 guiOffset(10, windowSize.y - gamescreen->getHpBarSize().y * 3.65);
    float posPauseX, posPauseY;

	// move camera
	//x 
	if (getMapSize().x > windowSize.x)
	{
		if (getPosition().x > windowSize.x / 2 && getPosition().x < getMapSize().x - windowSize.x / 2)
		{
			getParent()->setPosition(-getPosition().x + windowSize.x / 2, getParent()->getPosition().y);
			gamescreen->setBarsPos(Vector2(getPosition().x - windowSize.x / 2 + guiOffset.x, getParent()->getPosition().y + guiOffset.y));
            posPauseX = getPosition().x - windowSize.x / 2;
		}
		else
		{
			if (getPosition().x < windowSize.x / 2)
			{
				getParent()->setPosition(0, getParent()->getPosition().y);
				gamescreen->setBarsPos(Vector2(guiOffset.x, getParent()->getPosition().y + guiOffset.y));
                posPauseX = 0;
			}
				

			if (getPosition().x > getMapSize().x - windowSize.x / 2)
			{
				getParent()->setPosition(-getMapSize().x + windowSize.x, getParent()->getPosition().y);
				gamescreen->setBarsPos(Vector2(getMapSize().x - windowSize.x + guiOffset.x, getParent()->getPosition().y + guiOffset.y));
                posPauseX = getMapSize().x - windowSize.x;
            }
		}
	}
    //y
	if (getMapSize().y > windowSize.y)
	{
		if (getPosition().y > windowSize.y / 2 && getPosition().y < getMapSize().y - windowSize.y / 2)
		{
            getParent()->setPosition(getParent()->getPosition().x, -getPosition().y + windowSize.y / 2);
			gamescreen->setBarsPos(Vector2(-getParent()->getPosition().x + guiOffset.x, getPosition().y - windowSize.y / 2 + guiOffset.y));
            posPauseY = getPosition().y - windowSize.y / 2;
        }
		else
		{
			if (getPosition().y < windowSize.y / 2)
			{
				getParent()->setPosition(getParent()->getPosition().x, 0);
				gamescreen->setBarsPos(Vector2(-getParent()->getPosition().x + guiOffset.x, guiOffset.y));
                posPauseY = 0;
			}

			if (getPosition().y > getMapSize().y - windowSize.y / 2)
			{
				getParent()->setPosition(getParent()->getPosition().x, -getMapSize().y + windowSize.y);
				gamescreen->setBarsPos(Vector2(-getParent()->getPosition().x + guiOffset.x, getMapSize().y - windowSize.y + guiOffset.y));
                posPauseY = getMapSize().y - windowSize.y;
            }
		}
	}
    gamescreen->setTextPausePosition(Vector2(posPauseX, posPauseY) + windowSize/2 - Vector2(115,50));
}

void Player::setNormalStateAnimation()
{
    setResAnim(persStandsDown);
}



void Player::rotate()
{
    if(isPunching)
    {
        if(moving)
        {
            if(dirX > 0)   //goes right
            {
                persAnimCurrent = persAnimRightAttack;
                orientation = right;
            }
            else if(dirX < 0)  //goes left
            {
                persAnimCurrent = persAnimRightAttack;
                orientation = left;
            }
            else
            {
                if(dirY > 0)   //goes down
                {
                    persAnimCurrent = persAnimDownAttack;
                    orientation = down;
                }
                else if(dirY < 0)  //goes up
                {
                    persAnimCurrent = persAnimUpAttack;
                    orientation = up;
                }
            }
            removeTweens();
            if(persAnimCurrent == persAnimRightAttack)
                tween = addTween(TweenAnim(persAnimCurrent), HorizontalAnimationDuration);
            else
                tween = addTween(TweenAnim(persAnimCurrent), VerticalAnimationDuration * 2);
        }
        else    //if not moving
        {
            removeTweens();

            if(dirX > 0)   //stands right
            {
                persAnimCurrent = persStandsRightAttack;
                orientation = right;
            }
            else if(dirX < 0)  //stands left
            {
                persAnimCurrent = persStandsRightAttack;
                orientation = left;
            }
            else    // dirX == 0
            {
                if(dirY > 0)   //stands down
                {
                    persAnimCurrent = persStandsDownAttack;
                    orientation = down;
                }
                else if(dirY < 0)  //stands up
                {
                    persAnimCurrent = persStandsUpAttack;
                    orientation = up;
                }
                else    // dirY == 0
                {
                    if(orientation == right || orientation == left)
                        persAnimCurrent = persStandsRightAttack;
                    else if(orientation == up)
                        persAnimCurrent = persStandsUpAttack;
                    else if(orientation == down)
                        persAnimCurrent = persStandsDownAttack;
                }
            }

            removeTweens();
            if(persAnimCurrent == persAnimRightAttack)
                tween = addTween(TweenAnim(persAnimCurrent), HorizontalAnimationDuration);
            else
                tween = addTween(TweenAnim(persAnimCurrent), VerticalAnimationDuration * 2);
        }

        tween->setDoneCallback(CLOSURE(this, &Player::onTweenDone));
    }
    else    // if not punching
    {
        if(moving)
        {
            if(dirX > 0)   //goes right
            {
                persAnimCurrent = persAnimRight;
                orientation = right;
            }
            else if(dirX < 0)  //goes left
            {
                persAnimCurrent = persAnimRight;
                orientation = left;
            }
            else
            {
                if(dirY > 0)   //goes down
                {
                    persAnimCurrent = persAnimDown;
                    orientation = down;
                }
                else if(dirY < 0)  //goes up
                {
                    persAnimCurrent = persAnimUp;
                    orientation = up;
                }
            }
            removeTweens();
            if(persAnimCurrent == persAnimRight)
                tween = addTween(TweenAnim(persAnimCurrent), HorizontalAnimationDuration, -1, true);
            else
                tween = addTween(TweenAnim(persAnimCurrent), VerticalAnimationDuration, -1);
        }
        else    //if not moving
        {
            removeTweens();

            if(dirX > 0)   //stands right
            {
                persAnimCurrent = persStandsRight;
                orientation = right;
            }
            else if(dirX < 0)  //stands left
            {
                persAnimCurrent = persStandsRight;
                orientation = left;
            }
            else    // dirX == 0
            {
                if(dirY > 0)   //stands down
                {
                    persAnimCurrent = persStandsDown;
                    orientation = down;
                }
                else if(dirY < 0)  //stands up
                {
                    persAnimCurrent = persStandsUp;
                    orientation = up;
                }
                else    // dirY == 0
                {
                    if(orientation == right || orientation == left)
                        persAnimCurrent = persStandsRight;
                    else if(orientation == up)
                        persAnimCurrent = persStandsUp;
                    else if(orientation == down)
                        persAnimCurrent = persStandsDown;
                }
            }

            if(persAnimCurrent == persStandsRight)
                setResAnim(persAnimCurrent, 1);
            else
                setResAnim(persAnimCurrent);
        }
    }

    setFlippedX(orientation == left);
}

int Player::getSign(const float number)
{
    if(number > 0)
        return 1;
    else if(number < 0)
        return -1;
    else
        return 0;
}

Direction Player::getOrientation()
{
    return orientation;
}


void Player::takeDamage(int damage)
{
    if (healthPoints > 0)
        healthPoints -= damage;
    else return;
    if(healthPoints <= 0) {
        std::cout << "RIP Nathan" << std::endl;
        persAnimCurrent = persDeath;
        setResAnim(persAnimCurrent);

		DethGame::instance()->isWin = false;
		DethGame::instance()->setScreen("Game over screen");
        // TODO: get rekt
    }
    std::cout << "Nathan -" << damage << "hp (" << healthPoints << ")" << std::endl;
}


RectT<Vector2> Player::getRectPlayer()
{
    RectT<Vector2> rect_player(getPosition(), getSize());
    rect_player.setPosition(rect_player.getLeftTop()-getSize()/2);

    return rect_player;
}


void Player::punch()
{
    if(intPunch < 1000)
        return;
    else
        intPunch = 0;

    switch(getOrientation())
    {
    case left:
        attackArea.setPosition(getPosition().x - attackArea.getWidth() + getSize().x/2, getPosition().y - attackArea.getHeight() / 2 + getSize().y/2);
        break;
    case right:
        attackArea.setPosition(getPosition().x + attackArea.getWidth() - getSize().x, getPosition().y - attackArea.getHeight() / 2 + getSize().y/2);
        break;
    case up:
        attackArea.setPosition(getPosition().x - getSize().x/3, getPosition().y - attackArea.getHeight() + getSize().y/3);
        break;
    case down:
        attackArea.setPosition(getPosition().x - getSize().x/3, getPosition().y + attackArea.getHeight()/2 + getSize().y/3);
        break;
    default:
        break;
    }

    attackArea.setPosition(attackArea.getLeftTop() - getSize()/2);

    PlayerPunchEvent punchEvent(attackArea, weaponDamage);
    dispatchEvent(&punchEvent);
}


RectT<Vector2> Player::getCollisionBox()
{
    RectT<Vector2> rect_player(getPosition(), getSize());
    rect_player.setPosition(rect_player.getLeftTop()-Vector2((rect_player.getSize().x)/2, 0));
    rect_player.setSize(rect_player.getSize().x, (rect_player.getSize().y)/2);

    return rect_player;
}


void Player::addBanana()
{
    bananaCount++;
	gamescreen->setBananas(bananaCount);
}

void Player::updatePunching(bool _isPunching)
{
    isPunchingOld = isPunching;
    isPunching = _isPunching;
}

void Player::onTweenDone(Event *event)
{
    log::messageln("tween done");
    updatePunching(false);
}

void Player::reset()
{
    setNormalStateAnimation();
    m_pause_mode = false;

    setPosition(position_spawn);
    pos = position_spawn;

    healthPoints = 500;
    bananaCount = 0;
}


int Player::getHP()
{
    return healthPoints;
}
