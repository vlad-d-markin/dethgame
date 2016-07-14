#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "player.h"
#include "dethgame.h"
#include <iostream>

using namespace oxygine;

Player::Player(GameScreen *gs) : Sprite()
{
    gamescreen = gs;

    VerticalAnimationDuration = 450;
    HorizontalAnimationDuration = 700;
    persAnimUp = gamescreen->getResources()->getResAnim("skin_goes_up");
    persAnimDown = gamescreen->getResources()->getResAnim("skin_goes_down");
    persAnimRight = gamescreen->getResources()->getResAnim("skin_goes_right");
    persStandsUp = gamescreen->getResources()->getResAnim("skin_stands_up");
    persStandsDown = gamescreen->getResources()->getResAnim("skin_stands_down");
    persStandsRight = gamescreen->getResources()->getResAnim("skin_goes_right");

    setResAnim(persStandsDown);
    orientation = down;
    moving = false;
    movingOld = false;
    dirX = 0;
    dirY = 0;
    dirXOld = 0;
    dirYOld = 0;

    pos = Vector2(300, 300);
    setPosition(pos);
    //Vnorm = ???
    healthPoints = 500;
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

	//calculate speed using delta time
    float speed = 150.0f * (us.dt / 1000.0f);

    //Vector2 pos = getPosition();
    dirXOld = dirX;
    dirYOld = dirY;
    dirX = 0;
    dirY = 0;

    if (data[SDL_SCANCODE_A]) dirX -= speed;
    if (data[SDL_SCANCODE_D]) dirX += speed;
    if (data[SDL_SCANCODE_W]) dirY -= speed;
    if (data[SDL_SCANCODE_S]) dirY += speed;

    //choose an appropriate animation
    if( getSign(dirX) != getSign(dirXOld)
        || ( getSign(dirX) == 0 && getSign(dirY) != getSign(dirYOld) )
        || getSign(moving) != getSign(movingOld) )
    {
        //std::cerr << "X=" << dirX << " Xo=" << dirXOld << " Y=" << dirY << " Yo=" << dirYOld << " M=" << moving << " Mo=" << movingOld << std::endl;
        rotate();
    }

	Vector2 windowSize(getParent()->getSize());

    //std::cout << (getMapSize().x > windowSize.x) << std::endl;

	// move camera
	//x 
	if (getMapSize().x > windowSize.x)
	{
		if (getPosition().x > windowSize.x / 2 && getPosition().x < getMapSize().x - windowSize.x / 2)
		{
			getParent()->setPosition(-getPosition().x + windowSize.x / 2, getParent()->getPosition().y);
		}
		else
		{
			if (getPosition().x < windowSize.x / 2)
			{
				getParent()->setPosition(0, getParent()->getPosition().y);
			}

			if (getPosition().x > getMapSize().x - windowSize.x / 2)
			{
				getParent()->setPosition(-getMapSize().x + windowSize.x, getParent()->getPosition().y);
			}
		}
	}
	
    //y
	if (getMapSize().y > windowSize.y)
	{
		if (getPosition().y > windowSize.y / 2 && getPosition().y < getMapSize().y - windowSize.y / 2)
		{
			getParent()->setPosition(getParent()->getPosition().x, -getPosition().y + windowSize.y / 2);
		}
		else
		{
			if (getPosition().y < windowSize.y / 2)
			{
				getParent()->setPosition(getParent()->getPosition().x, 0);
			}

			if (getPosition().y > getMapSize().y - windowSize.y / 2)
			{
				getParent()->setPosition(getParent()->getPosition().x, -getMapSize().y + windowSize.y);
			}
		}
	}
}

void Player::rotate()
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
        removeTween(tween);
        if(persAnimCurrent == persAnimRight)
            tween = addTween(TweenAnim(persAnimCurrent), HorizontalAnimationDuration, -1, true);
        else
            tween = addTween(TweenAnim(persAnimCurrent), VerticalAnimationDuration, -1);
    }
    else    //if not moving
    {
        removeTween(tween);

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

direction Player::getOrientation()
{
    return orientation;
}
