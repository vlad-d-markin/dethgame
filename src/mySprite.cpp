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

	if (getPosition().x > getParent()->getParent()->getSize().x / 2)
	{
		getParent()->setPosition(-getPosition().x + getParent()->getParent()->getSize().x / 2, getParent()->getPosition().y);
	}

	if (getPosition().y > getParent()->getParent()->getSize().y / 2)
	{
		getParent()->setPosition(getParent()->getPosition().x, -getPosition().y + getParent()->getParent()->getSize().y / 2);
	}
}
