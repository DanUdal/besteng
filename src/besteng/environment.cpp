#include "environment.h"

namespace besteng
{
	void Environment::updateDeltaTime()
	{
		thisTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks(); //updates the time that the last frame took
    }

	void Environment::frameCap()
	{
		if (thisTime - (1.0f / 60.0f) < 0)
		{
			SDL_Delay((1.0f / 60.0f) - (thisTime * 1000.0f));
			deltaTime = 1.0f / 60.0f; //if the frame took less than 16.7 ms set delta time to 60 fps
		}
		else
		{
			deltaTime = thisTime; //if the frame took longer set delta time to that
		}
	}

	Environment& Environment::operator=(const Environment&)
	{

	}
}
