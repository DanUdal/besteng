#include "entity.h"

namespace besteng //functions to call all the components
{
	void Entity::tick()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->tick();
		}
	}

	void Entity::render()
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->onRender();
		}
	}

	void Entity::collision(Collider other)
	{
		for (size_t ci = 0; ci < components.size(); ci++)
		{
			components.at(ci)->onCollision(other);
		}
	}
}