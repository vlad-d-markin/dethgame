#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include <iostream>

using namespace oxygine;

class MySprite : public Sprite
{
protected:
	void doUpdate(const UpdateState &us);
};

typedef ::oxygine::intrusive_ptr<MySprite> spMySprite;