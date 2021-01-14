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
#include "Renderer.h"

namespace besteng
{
	struct Core
	{
	private:
		Core(); //private constructor so the user must use initialise
		SDL_Window* window; //window pointer for sdl
		Core& operator=(const Core&); //this makes core uncopiable
		std::shared_ptr<Entity> currentScreen; //holds the current main camera
		bool GJK(std::shared_ptr<Collider> ObjectA, std::shared_ptr<Collider> ObjectB); //this function calculates if the 2 objects collide
		void collisionTest(); //tests for collision between all entities in the scene
	public:
		static std::shared_ptr<Core> initialise(); //initialises the core for the engine
		std::shared_ptr<Entity> addEntity(std::string name); //2 overloads for add entity with one defaulting to 0 and the other taking a transform for the starting position
		std::shared_ptr<Entity> addEntity(std::string name, std::shared_ptr<Transform> position); 
		void start(); //runs the game's main loop
		SDL_GLContext glContext; //contains the context for sdl
		std::shared_ptr<rend::Context> context; //context for rend
		std::shared_ptr<Entity> getCurrentScreen()
		{
			return currentScreen;
		}
		std::shared_ptr<InputManager> Input; //the input manager contains all keyboard and button inputs
		std::vector<std::shared_ptr<Entity>> entities; //vector of all entities in the scene
		std::weak_ptr<Core> self; //self pointer
		std::shared_ptr<Environment> environment; //the environment holds system variables such as delta time
		std::shared_ptr<Entity> findEntity(std::string name); //finds entity of a given name
	};
}