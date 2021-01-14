#pragma once
#include <memory>
#include <vector>
#include "entity.h"
#include "rend/rend.h"
#include <SDL2/SDL.h>
#include "rend/Exception.h"
#include "environment.h"
#include "screen.h"
#include "transform.h"
#include "inputManager.h"
#include "collider.h"

namespace besteng
{
	struct Core
	{
	private:
		std::vector<std::shared_ptr<Entity>> entities;
		std::weak_ptr<Core> self;
		std::shared_ptr<Environment> environment;
		Core();
		SDL_Window* window;
		Core& operator=(const Core&);
		std::shared_ptr<Entity> currentScreen;
		std::shared_ptr<InputManager> Input;
		bool GJK(std::shared_ptr<Collider> ObjectA, std::shared_ptr<Collider> ObjectB);
		void collisionTest();
	public:
		static std::shared_ptr<Core> initialise();
		std::shared_ptr<Entity> addEntity(std::string name);
		std::shared_ptr<Entity> addEntity(std::string name, std::shared_ptr<Transform> position);
		void start();
		SDL_GLContext glContext;
		std::shared_ptr<rend::Context> context;
		std::shared_ptr<Entity> getCurrentScreen()
		{
			return currentScreen;
		}
	};
}