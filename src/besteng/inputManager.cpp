#include "inputManager.h"

void besteng::InputManager::checkInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_KEYDOWN: keyDown.push_back(event.key.keysym.sym);
			keyPressed.push_back(event.key.keysym.sym);
		case SDL_KEYUP: keyUp.push_back(event.key.keysym.sym);
			for (auto it = std::begin(keyPressed); it != std::end(keyPressed); it++)
			{
				if (*it == event.key.keysym.sym)
				{
					keyPressed.erase(it);
					it--;
				}
			}
		case SDL_MOUSEBUTTONDOWN: mouseDown.push_back(event.button.button);
			mousePressed.push_back(event.button.button);
		case SDL_MOUSEBUTTONUP: mouseUp.push_back(event.button.button);
			for (auto it = std::begin(mousePressed); it != std::end(mousePressed); it++)
			{
				if (*it == event.button.button)
				{
					mousePressed.erase(it);
					it--;
				}
			}
		}
	}
}

bool besteng::InputManager::getKeyboardInput(int key)
{
	for (auto it = std::begin(keyPressed); it != std::end(keyPressed); it++)
	{
		if (*it == key)
		{
			return true;
		}
	}
	return false;
}

bool besteng::InputManager::getMouseInput(int button)
{
	for (auto it = std::begin(mousePressed); it != std::end(mousePressed); it++)
	{
		if (*it == button)
		{
			return true;
		}
	}
	return false;
}

void besteng::InputManager::clear()
{
	keyDown.clear();
	keyUp.clear();
	mouseDown.clear();
	mouseUp.clear();
}
