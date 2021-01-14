#include "environment.h"

namespace besteng
{
	void Environment::updateDeltaTime()
	{
		deltaTime = (SDL_GetTicks() - lastTime) / 1000.0f;
		lastTime = SDL_GetTicks();
    }

	void Environment::frameCap()
	{
		if (deltaTime - (1.0f / 60.0f) < 0)
		{
			SDL_Delay((1.0f / 60.0f) - (deltaTime * 1000.0f));
		}
	}

	Environment& Environment::operator=(const Environment&)
	{

	}
}
