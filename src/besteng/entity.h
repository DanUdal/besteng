#pragma once
#include <vector>
#include <memory>
#include <string>
#include "core.h"

namespace besteng
{
	struct Component;
	struct Exception;
	struct Entity
	{
	friend struct Core;
	private:
		std::vector<std::shared_ptr<Component>> components;
		void tick();
		void render();
		void collision(Collider other);
		std::weak_ptr<Entity> self;
		std::weak_ptr<Core> core;
	public:
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>();

			components.push_back(rtn);

			rtn->entity = self;

			rtn->self = rtn;

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> addComponent(std::shared_ptr<T> component)
		{
			components.push_back(component);

			component->entity = self;

			component->self = rtn;

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> getComponent()
		{
			std::shared_ptr<T> rtn = NULL;
			for (ci = 0; ci < components.size(); ci++)
			{
				rtn = std::dynamic_pointer_cast<T>(components.at(ci));

				if (rtn)
				{
					return rtn;
				}
			}

			throw Exception("Cannot find component type");
		}
		std::shared_ptr<Core> getCore()
		{
			return core.lock();
		}
		std::string name;
		std::shared_ptr<Screen> getCurrentScreen()
		{
			return getCore()->getCurrentScreen()->getComponent<Screen>();
		}
	};
}