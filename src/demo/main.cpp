#include <iostream>
#include "besteng/besteng.h"

struct player : private Component
{

};

int main(int argc, char* argv[])
{	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		throw std::exception();
	}
	
	std::shared_ptr<Core> core = Core::initialise();

	core->start();

	return 0;
}