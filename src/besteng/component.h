#ifndef BESTENG_COMPONENT_H
#define BESTENG_COMPONENT_H
#include <memory>
#include <iostream>
#include "entity.h"
#include "screen.h"
#include "collider.h"

namespace besteng
{
	struct Screen;
	struct Core;
	struct Component
	{
		friend class Entity;
		std::shared_ptr<Entity> getEntity()
		{
			return entity.lock(); 
		}
		std::shared_ptr<Screen> getCurrentScreen()
		{
			return getEntity()->getCore()->getCurrentScreen()->getComponent<Screen>(); //this function exists to remove the need for coding so many getters to improve UX
		}
	protected:
		void tick();
		virtual void onInitialise();
		virtual void onTick();
		virtual void onRender();
		virtual void onCollision(Collider other);
		std::weak_ptr<Entity> entity; //pointer up the hierarchy and to self
		std::weak_ptr<Component> self;
	};

}
#endif