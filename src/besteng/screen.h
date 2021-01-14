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
		int windowWidth;
		int windowHeight;
		float fov;
		float near;
		float far;
		std::weak_ptr<Core> core;
	public:
		int getWidth()
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
		rend::mat4 getPerspective()
		{
			return rend::perspective(fov, float(windowWidth / windowHeight), near, far);
		}
	};
}