#pragma once
#include <SDL2/SDL.h>
#include <memory>

namespace besteng
{
	struct Environment //an environment to handle system parameters such as delta time
	{
		friend struct Core;
		float deltaTime; //stores delta time
		float lastTime;
		float thisTime;
	private:
		std::weak_ptr<Core> core; //core and self pointers
		std::weak_ptr<Environment> self;
		Environment& operator=(const Environment&); //makes the environment uncopyable
		void updateDeltaTime();
		void frameCap();
		Environment() //private constructor
		{
			lastTime = SDL_GetTicks(); //sets the initial value for last time
		}
	};
}