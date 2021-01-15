#pragma once
#include "rend/mathutil.h"
#include <memory>
#include "component.h"

namespace besteng
{
	struct Screen : public Component
	{
		friend struct Core;
	private:
		int windowWidth; //screen component that contains all the variables for a camera used in a perspective matrix
		int windowHeight;
		float fov;
		float near;
		float far;
		std::weak_ptr<Core> core;
	public:
		int getWidth() //getters for every variable
		{
			return windowWidth;
		}
		int getHeight()
		{
			return windowHeight;
		}
		float getFOV()
		{
			return fov;
		}
		float getNear()
		{
			return near;
		}
		float getFar()
		{
			return far;
		}
		glm::mat4 getPerspective()
		{
			return rend::perspective(fov, float(windowWidth / windowHeight), near, far);
		}
	};
}