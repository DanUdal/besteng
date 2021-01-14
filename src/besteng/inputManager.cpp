#include "inputManager.h"


namespace besteng
{
	void InputManager::checkInput() //checks all current events using sdl
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_KEYDOWN: keyDown.push_back(event.key.keysym.sym);
				keyPressed.push_back(event.key.keysym.sym); //keyboard key pressed down
			case SDL_KEYUP: keyUp.push_back(event.key.keysym.sym); //keyboard key released
				for (auto it = std::begin(keyPressed); it != std::end(keyPressed); it++)
				{
					if (*it == event.key.keysym.sym)
					{
						keyPressed.erase(it); //find the key released in the list of keys pressed and remove it
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
						mousePressed.erase(it); //same as keyboard but for mouse
						it--;
					}
				}
			case SDL_QUIT: quit = true;
			}
		}
	}

	bool InputManager::getKeyboardInput(int key)
	{
		for (auto it = std::begin(keyPressed); it != std::end(keyPressed); it++)
		{
			if (*it == key)
			{
				return true; //searches for a key press with the specific keysym and returns true if it's found
			}
		}
		return false;
	}

	bool InputManager::getMouseInput(int button)
	{
		for (auto it = std::begin(mousePressed); it != std::end(mousePressed); it++)
		{
			if (*it == button)
			{
				return true; //checks for mouse buttons pressed
			}
		}
		return false;
	}

	void InputManager::clear()
	{
		keyDown.clear();
		keyUp.clear();
		mouseDown.clear();
		mouseUp.clear();
	}

	//functions to check the other input vectors for the user
	bool InputManager::findKeyUp(int key)
	{
		for (auto it = std::begin(keyUp); it != std::end(keyUp); it++)
		{
			if (*it == key)
			{
				return true;
			}
		}
		return false;
	}
	bool InputManager::findKeyDown(int key)
	{
		for (auto it = std::begin(keyDown); it != std::end(keyDown); it++)
		{
			if (*it == key)
			{
				return true; 
			}
		}
		return false;
	}
	bool InputManager::findMouseUp(int button)
	{
		for (auto it = std::begin(mouseUp); it != std::end(mouseUp); it++)
		{
			if (*it == button)
			{
				return true;
			}
		}
		return false;
	}
	bool InputManager::findMouseDown(int button)
	{
		for (auto it = std::begin(mouseDown); it != std::end(mouseDown); it++)
		{
			if (*it == button)
			{
				return true;
			}
		}
		return false;
	}
}