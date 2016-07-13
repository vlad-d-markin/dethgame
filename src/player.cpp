#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "player.h"
#include "dethgame.h"
#include <iostream>
#include <cmath>

using namespace oxygine;

Player::Player() : Sprite()
{
    my_resources = new Resources();
    my_resources->loadXML("res.xml");
    resAnim = my_resources->getResAnim("button_with_arrow");
    this->setResAnim(resAnim);

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

Vector2 Player::getDirectionX()
{
    return Vector2(dirX, 0);
}

Vector2 Player::getDirectionY()
{
    return Vector2(0, dirY);
}

void Player::moveX()
{
    pos.x += dirX;
    setPosition(pos);
}

void Player::moveY()
{
    pos.y += dirY;
    setPosition(pos);
}

void Player::doUpdate(const UpdateState &us)
{
	const Uint8* data = SDL_GetKeyboardState(0);

	//calculate speed using delta time
    float speed = 100.0f * (us.dt / 1000.0f);

    //Vector2 pos = getPosition();
    dirX = 0;
    dirY = 0;

    if (data[SDL_SCANCODE_A]) dirX -= speed;
    if (data[SDL_SCANCODE_D]) dirX += speed;
    if (data[SDL_SCANCODE_W]) dirY -= speed;
    if (data[SDL_SCANCODE_S]) dirY += speed;

    //rotate player
    if(! ( ( dirX == 0 ) && ( dirY == 0 ) ) )
        this->setRotation(atan2(dirY, dirX));

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
	
    //
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
