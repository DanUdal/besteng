#pragma once
#include <SDL2/SDL.h>
#include <memory>

namespace besteng
{
	struct Environment
	{
		friend struct Core;
		float deltaTime;
		float lastTime;
	private:
		std::weak_ptr<Core> core;
		std::weak_ptr<Environment> self;
		Environment& operator=(const Environment&);
		void updateDeltaTime();
		void frameCap();
		Environment()
		{
			lastTime = SDL_GetTicks();
		}
	};
}