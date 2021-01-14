#include "Renderer.h"
#include "rend/mathutil.h"
#include "mesh.h"

namespace besteng
{
	Renderer::Renderer()
	{
	}


	Renderer::~Renderer()
	{
	}

	std::shared_ptr<Renderer> Renderer::initialise() //initialises the shader for the renderer
	{
		std::shared_ptr<Renderer> rtn = std::make_shared<Renderer>();
		rtn->context = rend::Context::initialize();
		rtn->shader = rtn->context->createShader(); //intialising variables
		rtn->self = rtn;
		//glsl source code for shader
		const char* src =
			"\n#ifdef VERTEX\n                       " \
			"attribute vec3 a_Position;              " \
			"attribute vec2 a_TexCoord;              " \
			"varying vec2 v_texcoord;                " \
			"uniform mat4 u_projection;		         " \
			"uniform mat4 u_model;                   " \
			"                                        " \
			"void main()                             " \
			"{                                       " \
			"  gl_Position = u_projection * u_model * vec4(a_Position, 1); " \
			"  v_texCoord = a_TexCoord               " \
			"}                                       " \
			"                                        " \
			"\n#endif\n                              " \
			"\n#ifdef FRAGMENT\n                     " \
			"         " \
			"uniform sampler2D u_Texture;            " \
			"varying vec2 v_texcoord;                " \
			"void main()                             " \
			"{                                       " \
			" vec4 tex = texture2D(u_texture, v_texcoord);" \
            " gl_FragColor = tex;                    " \
			"}                                       " \
			"                                        " \
			"\n#endif\n                              ";
		rtn->shader->parse(src); //sends program to the shader
		return rtn;
	}

	void Renderer::onRender()
	{
		std::shared_ptr<Mesh> mesh = entity.lock()->getComponent<Mesh>();
		if (mesh) //if there is a mesh to render then render the object
		{
			shader->setUniform("u_model", getEntity()->getComponent<Transform>()->getModel()); //places the object in view space
			shader->setUniform("u_projection", getCurrentScreen()->getPerspective());
			shader->render();
		}
	}

	void Renderer::onInitialise()
	{

	}
}
