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
        std::shared_ptr<rend::Texture> texture;
        std::string fileLoc;
        void initialise(std::string path);
        void addTexture(char* path);
        void scale();
    };
}