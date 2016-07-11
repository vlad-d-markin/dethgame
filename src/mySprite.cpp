#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include "mySprite.h"
#include <iostream>

using namespace oxygine;

void MySprite::doUpdate(const UpdateState &us)
{
	const Uint8* data = SDL_GetKeyboardState(0);

	//calculate speed using delta time
    float speed = 500.0f * (us.dt / 1000.0f);

	Vector2 pos = getPosition();

	if (data[SDL_SCANCODE_A]) pos.x -= speed;
	if (data[SDL_SCANCODE_D]) pos.x += speed;
	if (data[SDL_SCANCODE_W]) pos.y -= speed;
	if (data[SDL_SCANCODE_S]) pos.y += speed;

	setPosition(pos);






    Vector2 windowSize(getParent()->getSize());

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
