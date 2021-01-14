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
		std::vector<std::shared_ptr<Component>> components; //a list of all the compoents attached to the entity
		void tick();
		void render();
		void collision(Collider other); //these call the corresponding functions in all the compoents for the entity
		std::weak_ptr<Entity> self;
		std::weak_ptr<Core> core; //pointers to self and core
	public:
		template <typename T>
		std::shared_ptr<T> addComponent()
		{
			std::shared_ptr<T> rtn = std::make_shared<T>(); //adds a component of the type specific with no variables set

			components.push_back(rtn);

			rtn->entity = self;

			rtn->self = rtn;

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> addComponent(std::shared_ptr<T> component)
		{
			components.push_back(component); //adds the compoent passed into the function allowing for intialisation

			component->entity = self;

			component->self = rtn; //sets poitners

			return rtn;
		}

		template <typename T>
		std::shared_ptr<T> getComponent() //returns the first component found of the specified type
		{ //no entity should have more than 1 component of each type
			std::shared_ptr<T> rtn = NULL;
			for (ci = 0; ci < components.size(); ci++)
			{
				rtn = std::dynamic_pointer_cast<T>(components.at(ci));

				if (rtn)
				{
					return rtn;
				}
			}

			throw Exception("Cannot find component type"); //sends an exception if no component found
		}
		std::shared_ptr<Core> getCore()
		{
			return core.lock();
		}
		std::string name; //stores the name of the entity
		std::shared_ptr<Screen> getCurrentScreen()
		{
			return getCore()->getCurrentScreen()->getComponent<Screen>(); //set of pointer calls to make getting the screen easier for the user
		}
	};
}