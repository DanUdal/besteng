#include "core.h"

namespace besteng
{
	std::shared_ptr<Core> Core::initialise()
	{
		std::shared_ptr<Core> rtn = std::shared_ptr<Core>(); //creates the shared pointer for the function to return

		rtn->self = rtn;

		rtn->window = SDL_CreateWindow("besteng", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, 800, 600,
			SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE); //creates the window to render everything to

		if (!rtn->window)
		{ 
			throw rend::Exception("Failed to create window"); //error handling
		}
		rtn->glContext = SDL_GL_CreateContext(rtn->window); //creates context for the window
		if (!rtn->glContext) 
		{ 
			throw rend::Exception("Failed to create OpenGL context");
		}
		rtn->context = rend::Context::initialize(); //initialises the rend context

		std::shared_ptr<Entity> camera = rtn->addEntity("main camera"); //adds the main camera to the scene as an entity

		rtn->currentScreen = camera;

		camera->addComponent<Screen>();

		camera->getComponent<Screen>()->core = rtn->self;
		camera->getComponent<Screen>()->windowWidth = 800;
		camera->getComponent<Screen>()->windowHeight = 600;
		camera->getComponent<Screen>()->fov = 45.0f;
		camera->getComponent<Screen>()->near = 1.0f;
		camera->getComponent<Screen>()->far = 1000.0f; //initialises the main camera's variables

		rtn->environment = std::make_shared<Environment>();

		rtn->environment->core = rtn->self;

		rtn->environment->self = rtn->environment; //initialises the environment

		rtn->Input = std::make_shared<InputManager>(); //initialises the input manager

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity(std::string name) //adds an entity at the default position with the name passed in
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		entities.push_back(rtn);

		rtn->self = rtn;

		rtn->core = self;

		rtn->name = name;

		std::shared_ptr<Transform> transform = rtn->addComponent<Transform>(); //all entities must have a transform component

		transform->position = glm::vec3(0, 0, 0);

		transform->rotation = glm::vec3(0, 0, 0);

		transform->scale = glm::vec3(1, 1, 1);

		std::shared_ptr<Renderer> renderer = Renderer::initialise();

		rtn->addComponent(renderer); //adds a renderer component by default

		return rtn;
	}

	std::shared_ptr<Entity> Core::addEntity(std::string name, std::shared_ptr<Transform> position) //adds an entity with the transform given
	{
		std::shared_ptr<Entity> rtn = std::make_shared<Entity>();

		entities.push_back(rtn);

		rtn->self = rtn;

		rtn->core = self;

		rtn->name = name;

		rtn->addComponent<Transform>(position);

		std::shared_ptr<Renderer> renderer = Renderer::initialise();

		rtn->addComponent(renderer); //adds a renderer component by default

		return rtn;
	}

	void Core::start() //runs the main game loop
	{
		SDL_Event events = { 0 }; //gets all events from the input
		bool running = true; //variable tracks if the game has ended
		while (running)
		{
			Input->checkInput(); //adds any inputs to the input manager
			
			if (Input->quit)
			{
				running = false; //if SDL_QUIT happens end the game loop
			}

			for (size_t ei = 0; ei < entities.size(); ei++)
			{
				entities.at(ei)->tick(); //calls the tick for all entity components
			}

			glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //sets a default background colour

			for (size_t ei = 0; ei < entities.size(); ei++) 
			{ 
				entities.at(ei)->render(); //renders all components for the entities
			}

			SDL_GL_SwapWindow(window); //finishes the render and displays to screen

			Input->clear(); //clears all single frame inputs
			environment->updateDeltaTime();
			environment->frameCap(); //updates deltaT and caps the frames to 60 fps
		}
	}

	std::shared_ptr<Entity> Core::findEntity(std::string name)
	{
		for (auto it = entities.begin(); it < entities.end(); it++)
		{
			if ((*it)->name == name) //checks the name against every entity until the target is found
			{
				return (*it);
			}
		}
		throw rend::Exception("Entity of that name not found");
	}

	Core & Core::operator=(const Core &)
	{
		
	}

	bool sameDirection(glm::vec3 direction, glm::vec3 aOrigin)
	{
		return glm::dot(direction, aOrigin) > 0; //returns true if the direction given is in the direction of the origin. it is 0 or below if the angle is > 90 degrees
	}

	bool line(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		glm::vec3 a = simplex->operator[](0); //gets the first 2 points from the simplex in order to create a line for the 1D test
		glm::vec3 b = simplex->operator[](1);

		glm::vec3 ab = b - a; //this creates the vector acting as the line
		glm::vec3 aOrigin = -a; //-a is a vector from a to the origin

		if (sameDirection(ab, aOrigin)) //if ab is pointing towards the origin
		{
			direction = glm::cross(ab, glm::cross(aOrigin, ab)); 
		} //this generates the next direction to look in by creating a vector perpendicular to ab on the same plane as ab and -a
		else 
		{
			simplex->operator=({a}); //if ab is not pointing towards the origin remove b from the simplex and set the direction to be towards the origin from a
			direction = aOrigin;
		}
		return false;
	}

	bool triangle(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		glm::vec3 a = simplex->operator[](0);
		glm::vec3 b = simplex->operator[](1);
		glm::vec3 c = simplex->operator[](2); //gets the 3 vertices of the triangle from the simplex for the 2D test

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		glm::vec3 aOrigin = -a; //generates 3 lines from a pointing towards b, c and the origin

		glm::vec3 abc = glm::cross(ab, ac); //creates a vector perpendicular to the plane creates by ab and ac

		if (sameDirection(glm::cross(abc, ac), aOrigin)) //if the vector perpendicular to the plane abc, ac which is a vector going straight up vertically is towards the origin
		{
			if (sameDirection(ac, aOrigin)) //if ac is in the direction of the origin
			{
				simplex->operator=({a, c}); //create a line between a and c
				direction = glm::cross(ac, glm::cross(aOrigin, ac)); //set the direction to be perpendicular to ac and the vector straight up from the plane it creates
			}
			else 
			{
				return line(simplex->operator=({a, b}), direction); //recalculate the 1D test with a and b with the same direction used on the triangle
			}
		}
		else 
		{
			if (sameDirection(glm::cross(ab, abc), aOrigin)) //if the vector created on the place abc, ab is in the direction of the origin
			{
				return line(simplex->operator=({a, b}), direction); //recalculates the 1D test with a and b
			}
			else 
			{
				if (sameDirection(abc, aOrigin))
				{
					direction = abc; //if abc is towards the origin then set the direction equal to abc
				}
				else 
				{
					simplex->operator=({a, c, b}); //give the simplex the vertices for the triangle
					direction = -abc; //if the direction is away from the origin set the direction to -abc to make it towards
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
		glm::vec3 d = simplex->operator[](3); //gets the 4 vertices for the tetrahedron from the simplex for the 3D test

		glm::vec3 ab = b - a;
		glm::vec3 ac = c - a;
		glm::vec3 ad = d - a;
		glm::vec3 aOrigin = -a; //creates a vector for each of the shape's sides and one towards the origin from a

		glm::vec3 abc = glm::cross(ab, ac);
		glm::vec3 acd = glm::cross(ad, ac);
		glm::vec3 abd = glm::cross(ab, ad); //creates a vector perpendicular to each side of the tetrahedron for testing against the origin line

		if (sameDirection(abc, aOrigin))
		{
			return triangle(simplex->operator=({a, b, c}), direction);
		}
		if (sameDirection(acd, aOrigin))
		{
			return triangle(simplex->operator=({a, c, d}), direction);
		}
		if (sameDirection(abd, aOrigin)) 
		{ //if any of the cross vectors are in the direction of the origin then the simplex does not contain the origin and a collision hasn't been detected
			return triangle(simplex->operator=({a, d, b}), direction);
		}
		return true;
	}

	bool nextSimplex(std::shared_ptr<Simplex> simplex, glm::vec3& direction)
	{
		switch (simplex->getSize()) //calls the function required based on the size of the simplex given
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
		//calculates the furthest distance between points inside each shape along an arbitrary line to get the first support function
		std::shared_ptr<Simplex> points; //creates an empty simplex
		points->self = points;
		points->pushFront(support); //initialises simplex with one point
		glm::vec3 direction = -support;

		while (true)
		{
			support = ObjectA->findFurthestPoint(direction) 
						- ObjectB->findFurthestPoint(-direction); //creates a new support function along the new direction created
			if (glm::dot(support, direction) <= 0)
			{
				return false; //if the support and direction are perpendicular to each other then there is no collision
			}
			points->pushFront(support); //adds the support point to the simplex
			if (nextSimplex(points, direction))
			{
				return true; //if this function calls the tetrahedron and that returns true then a collision has been found
			}
		}
		return false; //must return along all possible lines
	}

	void Core::collisionTest()
	{
		for (auto it1 = entities.begin(); it1 < entities.end(); it1++)
		{
			for (auto it2 = entities.begin(); it2 < entities.end(); it2++) //iterate through each entity and check it for collision with each other entity
			{
				if ((*it1) != (*it2)) //if the objects being checked are not the same object
				{
					std::shared_ptr<Collider> col1 = (*it1)->getComponent<Collider>();
					std::shared_ptr<Collider> col2 = (*it2)->getComponent<Collider>(); //get the colliders for each object
					if (col1 && col2) //if both objects have a collider attached
					{
						bool collision; //collision test variable
						glm::vec3 pos1 = (*it1)->getComponent<Transform>()->position;
						glm::vec3 pos2 = (*it2)->getComponent<Transform>()->position; //gets the postion of te objects for the broad test
						if (glm::distance(pos1, pos2) <= (col1->maxDis + col2->maxDis)) //if the spheres around the objects don't collide don't test further
						{ //done for effieicnecy
							if ((col1->mesh) || (col2->mesh))
							{
								collision = GJK(col1, col2); //if either object has a mesh then do GJK
							}
							else
							{
								collision = true; //if both objects are a sphere then the collision has already been tested
							}
						}
						else
						{
							collision = false; 
						}
						if (collision)
						{
							(*it1)->collision(col2);
							(*it2)->collision(col1); //calls the collision function for both objects
						}
					}
				}
			}
		}
	}
}