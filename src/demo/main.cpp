#include <iostream>
#include "besteng/besteng.h"

struct Player : public Component
{
	std::shared_ptr<Transform> transform;
	void onInitialise()
	{
		transform = entity.lock()->getComponent<Transform>(); //on creating this entity get the transform of the entity
	}
	void onTick()
	{
		transform->position.x += 1; //every frame add 1 to x value
		if (entity.lock()->getCore()->Input->getKeyboardInput(SDLK_DOWN))
		{
			transform->position.x -= 2; //if the down key is pressed subtract from x value instead
		}
	}
};

int main(int argc, char* argv[])
{	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception(); //initialise SDL
	}
	
	std::shared_ptr<Core> core = Core::initialise(); //initialise core

	std::shared_ptr player = core->addEntity("player"); //add an entity called player to the scene

	player->addComponent<Player>(); //add the player component to player

	std::shared_ptr<Mesh> mesh = player->addComponent<Mesh>(); //add a mesh component to player and initialise the mesh and texture of it

	mesh->initialise("src\demo\aamltryjypkw-Male\Male.OBJ");

	mesh->addTexture("src\demo\aamltryjypkw-Male\!$Gate1");

	core->start(); //begin game loop

	return 0;
}