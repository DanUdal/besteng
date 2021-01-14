#include "component.h"

namespace besteng
{
	void Component::tick()
	{
		onTick();
	}

	void Component::onInitialise() //functions for the user to derive from in which they can put their own code
	{

	}

	void Component::onTick()
	{
		
	}

	void Component::onRender()
	{

	}

	void Component::onCollision(Collider other)
	{
		
	}
}