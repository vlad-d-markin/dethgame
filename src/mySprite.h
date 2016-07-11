#include "SDL.h"
#include "SDL_keyboard.h"
#include "core/oxygine.h"
#include "Sprite.h"
#include <iostream>

using namespace oxygine;

class MySprite : public Sprite
{
private: 
	Vector2 mapSize;
protected:
	void doUpdate(const UpdateState &us);
public: 
	void setMapSize(Vector2 _mapSize) { mapSize = _mapSize; }
	Vector2 getMapSize() const { return mapSize; }
};

typedef ::oxygine::intrusive_ptr<MySprite> spMySprite;