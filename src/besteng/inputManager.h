#pragma once
#include <memory>
#include <vector>
#include <SDL2/SDL.h>

namespace besteng
{
	struct InputManager
	{
	friend struct Core;
	private:
		std::vector<int> keyDown;
		std::vector<int> keyUp;
		std::vector<int> keyPressed;
		std::vector<int> mouseDown;
		std::vector<int> mousePressed;
		std::vector<int> mouseUp;
		void clear();
		void checkInput();
	public:
		bool getKeyboardInput(int key);
		bool getMouseInput(int button);
	};
}