#pragma once
#include "rend/rend.h"
#include "rend/mathutil.h"
#include "component.h"

namespace besteng
{
	struct Core;
	struct Renderer : public Component
	{
	private:
		std::shared_ptr<rend::Shader> shader; //each renderer has a shader and context
		std::shared_ptr<rend::Context> context;
		std::weak_ptr<Renderer> self; //self pointer
	public:
		Renderer();
		~Renderer();
		static std::shared_ptr<Renderer> initialise(); 
		void onRender();
		void onInitialise();
	};
}

