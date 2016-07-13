/*#include "core/oxygine.h"
#include "map.h"
#include <iostream>

using namespace oxygine;

#include "SDL_main.h"
#include "SDL.h"

int main(int argc, char* argv[])
{
	Map map("example.tmx");
		
	system("pause");
	return 0;
}*/

/*#include "core/oxygine.h"
#include "map.h"
#include <iostream>

using namespace oxygine;

#include "SDL_main.h"
#include "SDL.h"

int main(int argc, char* argv[])
{

	system("pause");
	return 0;
}*/






#include "core/oxygine.h"
#include "Stage.h"
#include "DebugActor.h"
#include "dethgame.h"

using namespace oxygine;


// This function is called each frame
int mainloop()
{
	// Update engine-internal components
	// If input events are available, they are passed to Stage::instance.handleEvent
	// If the function returns true, it means that the user requested the application to terminate
	bool done = core::update();

	// It gets passed to our example game implementation
	DethGame::instance()->update();

	// Update our stage
	// Update all actors. Actor::update will also be called for all its children
	getStage()->update();

	if (core::beginRendering())
	{
		Color clearColor(32, 32, 32, 255);
		Rect viewport(Point(0, 0), core::getDisplaySize());
		// Render all actors inside the stage. Actor::render will also be called for all its children
		getStage()->render(clearColor, viewport);

		core::swapDisplayBuffers();
	}

	return done ? 1 : 0;
}

// Application entry point
void run()
{
	ObjectBase::__startTracingLeaks();

	// Initialize Oxygine's internal stuff
	core::init_desc desc;
	desc.title = "Dethgame";

#if OXYGINE_SDL || OXYGINE_EMSCRIPTEN
	// The initial window size can be set up here on SDL builds
    desc.w = 1024;
	desc.h = 576;
	// Marmalade settings can be modified from the emulator's menu
#endif

	DethGame::instance()->preInit();
	core::init(&desc);


	// Create the stage. Stage is a root node for all updateable and drawable objects
	Stage::instance = new Stage(true);
	Point size = core::getDisplaySize();
	getStage()->setSize(size);

	// DebugActor is a helper actor node. It shows FPS, memory usage and other useful stuff
	DebugActor::show();

	// Initializes our example game. See example.cpp
	DethGame::instance()->init();

	// This is the main game loop.
	while (1)
	{
		int done = mainloop();
		if (done)
			break;
	}
	/*
	If we get here, the user has requested the Application to terminate.
	We dump and log all our created objects that have not been freed yet
	*/
	ObjectBase::dumpCreatedObjects();

	/*
	Let's clean up everything right now and call ObjectBase::dumpObjects() again.
	We need to free all allocated resources and delete all created actors.
	All actors/sprites are smart-pointer objects and don't need to be removed by hand.
	But now we want to delete it by hand.
	*/

	// See example.cpp for the shutdown function implementation
	DethGame::instance()->destroy();


	//renderer.cleanup();

	// Releases all internal components and the stage
	core::release();

	// The dump list should be empty by now,
	// we want to make sure that there aren't any memory leaks, so we call it again.
	ObjectBase::dumpCreatedObjects();

	ObjectBase::__stopTracingLeaks();
	//end
}

#ifdef OXYGINE_SDL

#include "SDL_main.h"
#include "SDL.h"

extern "C"
{
	void one(void* param) { mainloop(); }
	void oneEmsc() { mainloop(); }

	int main(int argc, char* argv[])
	{
		run();
		return 0;
	}
};
#endif
