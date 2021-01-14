#include "core.h"

namespace besteng
{
	std::shared_ptr<Core> Core::initialise()
	{
		std::shared_ptr<Core> rtn = std::shared_ptr<Core>();

		rtn->self = rtn;

		rtn->window = SDL_CreateWindow("besteng", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 800, 600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

		if (!rtn->window)
		{ 
			throw rend::Exception("Failed to create window");
		}
		rtn->glContext = SDL_GL_CreateContext(rtn->window);
		if (!rtn->glContext) 
		{ 
			throw rend::Exception("Failed to create OpenGL context");
		}
		rtn->context = rend::Context::initialize();

		std::shared_ptr<Entity> camera = rtn->addEntity("main camera");

		rtn->currentScreen = camera;

		camera->addComponent<Screen>();

		camera->getComponent<Screen>()->core = rtn->self;
		camera->getComponent<Screen>()->windowWidth = 800;
		camera->getComponent<Screen>()->windowHeight = 600;
		camera->getComponent<Screen>()->fov = 45.0f;
		camera->getComponent<Screen>()->near = 1.0f;
		camera->getComponent<Screen>()->far = 1000.0f;
		camera->name = "Main Camera";

		rtn->environment = std::make_shared<Environment>();

		rtn->environment->core = rtn->self;

		rtn->environment->self = rtn->environment;

		rtn->Input = std::make_shared<InputManager>();

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity(std::string name)
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		entities.push_back(rtn);

		rtn->self = rtn;

		rtn->core = self;

		rtn->name = name;

		std::shared_ptr<Transform> transform = rtn->addComponent<Transform>();

		transform->position = glm::vec3(0, 0, 0);

		transform->rotation = glm::vec3(0, 0, 0);

		transform->scale = glm::vec3(1, 1, 1);

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity(std::string name, std::shared_ptr<Transform> position)
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		entities.push_back(rtn);

		rtn->self = rtn;

		rtn->core = self;

		rtn->name = name;

		rtn->addComponent<Transform>(position);

		return rtn;
	}

	void Core::start()
	{
		SDL_Event events = { 0 };
		bool running = true;
		while (running)
		{
			while (SDL_PollEvent(&events) != 0)
			{
				if (events.type == SDL_QUIT)
				{
					running = false;
				}
			}

			Input->checkInput();

			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick();
			}

			glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			for (size_t ei = 0; ei < entities.size(); ei++) 
			{ 
				entities.at(ei)->render(); 
			}

			SDL_GL_SwapWindow(window);

			Input->clear();
		}
	}
	Core & Core::operator=(const Core &)
	{
		
	}

	bool sameDirection(glm::vec3 direction, glm::vec3 aOrigin)
	{
		return glm::dot(direction, aOrigin) > 0;
	}

	bool line(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		glm::vec3 a = simplex->operator[](0);
		glm::vec3 b = simplex->operator[](1);

		glm::vec3 ab = b - a;
		glm::vec3 aOrigin = -a;

		if (sameDirection(ab, aOrigin))
		{
			direction = glm::cross(ab, glm::cross(aOrigin, ab));
		}
		else 
		{
			simplex->operator=({a});
			direction = aOrigin;
		}
		return false;
	}

	bool triangle(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		glm::vec3 a = simplex->operator[](0);
		glm::vec3 b = simplex->operator[](1);
		glm::vec3 c = simplex->operator[](2);

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		glm::vec3 aOrigin = -a;

		glm::vec3 abc = glm::cross(ab, ac);

		if (sameDirection(glm::cross(abc, ac), aOrigin))
		{
			if (sameDirection(ac, aOrigin))
			{
				simplex->operator=({a, c});
				direction = glm::cross(ac, glm::cross(aOrigin, ac));
			}
			else 
			{
				return line(simplex->operator=({a, b}), direction);
			}
		}
		else 
		{
			if (sameDirection(glm::cross(ab, abc), aOrigin))
			{
				return line(simplex->operator=({a, b}), direction);
			}
			else 
			{
				if (sameDirection(abc, aOrigin))
				{
					direction = abc;
				}
				else 
				{
					simplex->operator=({a, c, b});
					direction = -abc;
				}
			}
		}
		return false;
	}

	bool tetrahedron(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		glm::vec3 a = simplex->operator[](0);
		glm::vec3 b = simplex->operator[](1);
		glm::vec3 c = simplex->operator[](2);
		glm::vec3 d = simplex->operator[](3);

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		glm::vec3 ad = d - a;
		glm::vec3 aOrigin = -a;

		glm::vec3 abc = glm::cross(ab, ac);
		glm::vec3 acd = glm::cross(ad, ac);
		glm::vec3 abd = glm::cross(ab, ad);

		if (sameDirection(abc, aOrigin))
		{
			return triangle(simplex->operator=({a, b, c}), direction);
		}
		if (sameDirection(acd, aOrigin))
		{
			return triangle(simplex->operator=({a, c, d}), direction);
		}
		if (sameDirection(abd, aOrigin))
		{
			return triangle(simplex->operator=({a, d, b}), direction);
		}
		return true;
	}

	bool nextSimplex(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		switch (simplex->getSize())
		{
			case 2: return line(simplex, direction);
			case 3: return triangle(simplex, direction);
			case 4: return tetrahedron(simplex, direction);
		}
	}

	bool Core::GJK(std::shared_ptr<Collider> ObjectA, std::shared_ptr<Collider> ObjectB)
	{
		glm::vec3 support = ObjectA->findFurthestPoint(glm::vec3(1,0,0)) 
						- ObjectB->findFurthestPoint(glm::vec3(-1,0,0));
		std::shared_ptr<Simplex> points;
		points->self = points;
		points->pushFront(support);
		glm::vec3 direction = -support;

		while (true)
		{
			support = ObjectA->findFurthestPoint(direction) 
						- ObjectB->findFurthestPoint(-direction);
			if (glm::dot(support, direction) <= 0)
			{
				return false;
			}
			points->pushFront(support);
			if (nextSimplex(points, direction))
			{
				return true;
			}
		}
		return false;
	}

	void Core::collisionTest()
	{
		for (auto it1 = entities.begin(); it1 < entities.end(); it1++)
		{
			for (auto it2 = entities.begin(); it2 < entities.end(); it2++)
			{
				std::shared_ptr<Collider> col1 = (*it1)->getComponent<Collider>();
				std::shared_ptr<Collider> col2 = (*it2)->getComponent<Collider>();
				if (col1 && col2)
				{
					bool collision;
					glm::vec3 pos1 = (*it1)->getComponent<Transform>()->position;
					glm::vec3 pos2 = (*it2)->getComponent<Transform>()->position;
					if (glm::distance(pos1, pos2) <= (col1->maxDis + col2->maxDis))
					{
						if ((col1->mesh) || (col2->mesh))
						{
							collision = GJK(col1, col2);
						}
						else
						{
							collision = true;
						}
					}
					else
					{
						collision = false;
					}
					if (collision)
					{
						(*it1)->collision(col2);
						(*it2)->collision(col1);
					}
				}
			}
		}
	}
}