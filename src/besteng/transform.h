#pragma once
#include "component.h"
#include "rend/mathutil.h"

namespace besteng
{
	struct Transform : public Component
	{
	private:

	public:
		rend::vec3 position;
		rend::vec3 rotation;
		rend::vec3 scale;
		rend::mat4 getModel()
		{
			rend::mat4 rotationx = rend::rotate(rotationx, rotation.x, rend::vec3(1, 0, 0));
			rend::mat4 rotationy = rend::rotate(rotationy, rotation.y, rend::vec3(0, 1, 0));
			rend::mat4 rotationz = rend::rotate(rotationz, rotation.z, rend::vec3(0, 0, 1));
			rend::mat4 translation = rend::translate(translation, position);
			rend::mat4 scalar = rend::scale(scalar, scale);
			return rotationx * rotationy * rotationz * translation * scalar;
		}
	};
}