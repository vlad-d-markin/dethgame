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

    pos = Vector2(300,300);
    setPosition(pos);

    //Vnorm = ???
    weaponDamage = 30;
    intPunch = 0;
    attackArea.setSize(80,80);

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

    bananaCount=0;
}

Vector2 Player::getDirection()
{
    return Vector2(dirX, dirY);
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
    intPunch += us.dt;

	const Uint8* data = SDL_GetKeyboardState(0);

	//calculate speed using delta time
    float speed = 500.0f * (us.dt / 1000.0f);

    //Vector2 pos = getPosition();
    dirX = 0;
    dirY = 0;

    if (data[SDL_SCANCODE_A]) dirX -= speed;
    if (data[SDL_SCANCODE_D]) dirX += speed;
    if (data[SDL_SCANCODE_W]) dirY -= speed;
    if (data[SDL_SCANCODE_S]) dirY += speed;
    if (data[SDL_SCANCODE_SPACE]) punch(WEST);

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

void Player::setDirection(float dir_x, float dir_y)
{
    dirX = dir_x;
    dirY = dir_y;
}


void Player::takeDamage(int damage)
{
    if((healthPoints -= damage) <= 0) {
        std::cout << "RIP Nathan" << std::endl;
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


void Player::punch(Direction dir)
{
    if(intPunch < 1000)
        return;
    else
        intPunch = 0;

    switch(dir)
    {
    case WEST:
        attackArea.setPosition(getPosition().x - attackArea.getWidth(), getPosition().y - attackArea.getHeight() / 2);
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
    std::cout<<"Banana count = "<<bananaCount<<std::endl;
}
