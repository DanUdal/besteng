#pragma once
#include "component.h"
#include "rend/mathutil.h"

namespace besteng
{
	struct Transform : public Component 
	{
	private:

	public:
		glm::vec3 position; //the transform component contains the position rotation and scale of all entities
		glm::vec3 rotation; //all entities must have a transform component
		glm::vec3 scale;
		glm::mat4 getModel()
		{
			rend::mat4 rotationx = rend::rotate(rotationx, rotation.x, rend::vec3(1, 0, 0));
			rend::mat4 rotationy = rend::rotate(rotationy, rotation.y, rend::vec3(0, 1, 0));
			rend::mat4 rotationz = rend::rotate(rotationz, rotation.z, rend::vec3(0, 0, 1));
			rend::mat4 translation = rend::translate(translation, position);
			rend::mat4 scalar = rend::scale(scalar, scale);
			return rotationx * rotationy * rotationz * translation * scalar; //returns a 4x4 matrix that transforms an from object space to world space
		}
	};
}