#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

namespace besteng
{
	struct InputManager //the input manager saves all inputs in vectors for the user to access
	{
	friend struct Core;
	private:
		std::vector<int> keyDown;
		std::vector<int> keyUp;
		std::vector<int> keyPressed;
		std::vector<int> mouseDown;
		std::vector<int> mousePressed;
		std::vector<int> mouseUp; //vectors tracking all the button presses
		void clear();
		void checkInput();
	public:
		bool getKeyboardInput(int key);
		bool findKeyUp(int key);
		bool findKeyDown(int key);
		bool findMouseUp(int key);
		bool findMouseDown(int key);
		bool getMouseInput(int button); //functions for the user to check inputs
	};
}