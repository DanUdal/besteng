#pragma once
#include <SDL2/SDL.h>
#include <memory>

namespace besteng
{
	struct environment
	{
		friend struct Core;
		float deltaTime;
		float lastTime;
		float frameRate;
	private:
		std::weak_ptr<Core> core;
		std::weak_ptr<environment> self;
		environment& operator=(const environment&);
		void updateDeltaTime();
		void frameCap();
		environment()
		{
			lastTime = SDL_GetTicks();
		}
		void setFrameRate(float newRate)
		{
			frameRate = newRate;
		}
	};
}