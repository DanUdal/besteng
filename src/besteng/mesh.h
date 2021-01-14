#define STB_IMAGE_IMPLEMENTATION
#include "component.h"
#include "rend/rend.h"
#include <fstream>
#include "glm/stb_image.h"

namespace besteng
{
    struct Mesh : public Component
    {
        std::shared_ptr<rend::Mesh> mesh;
        std::shared_ptr<rend::Texture> texture; //variables containing the mesh and texture data
        void initialise(std::string path); //initialises the mesh taking the path to a model file
        void addTexture(char* path); //adds a texture to the mesh
        //void scale();
    };
}