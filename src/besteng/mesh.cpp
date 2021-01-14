#include "mesh.h"

namespace besteng
{
    void Mesh::initialise(std::string path)
    {
        std::string fileStr;
        std::fstream file(path, std::fstream::in); //loads the file from the path given
        file >> fileStr; //sends the contents of the file to a string variable
        file.close(); //closes file after use
        mesh = std::make_shared<rend::Mesh>();
        mesh->parse(fileStr); //creates the mesh variable and uses rend to parse the file
    }

    /*void Mesh::scale() //unused scale function
    {
        std::shared_ptr<rend::Buffer> buffer = mesh->getBuffer("a_Position");
        int size = buffer->getSize();
        std::shared_ptr<Transform> transform = entity.lock()->getComponent<Transform>();
        for (int i = 0; i < size; i + 3)
        {
            glm::vec4 newPos = {buffer->floatData[i], buffer->floatData[i + 1], buffer->floatData[i + 2], 1};
            newPos = newPos * transform->getModel();
            buffer->floatData[i] = newPos[i];
            buffer->floatData[i + 1] = newPos[i + 1];
            buffer->floatData[i + 2] = newPos[i + 2];
        }
    }*/

    void Mesh::addTexture(char* path)
    {
        texture = std::make_shared<rend::Texture>(); //using rend to handle the texture
        unsigned char* fileStr;
        int x, y, n;
        fileStr = stbi_load(path, &x, &y, &n, 0); //using stbi_load to remove unneeded data from the image file such as headers
        //fileStr becomes a char list of colours
        if (fileStr != NULL)
        {
            for (int yPos; yPos < y; yPos++)
            {
                for (int i = 0, int xPos; xPos < x; i + n, xPos++)
                {
                    if (n == 3)
                    {
                        texture->setPixel(xPos, yPos, glm::vec3(fileStr[i] - '0', fileStr[i + 1] - '0', fileStr[i + 2] - '0')); //if bit depth is 3 then just rgb
                    }
                    if (n == 4)
                    {
                        texture->setPixel(xPos, yPos, glm::vec4(fileStr[i] - '0', fileStr[i + 1] - '0', fileStr[i + 2] - '0', fileStr[i + 3] - '0'));
                    } //if depth is 4 then rgba
                }
            }
        }
        mesh->setTexture("u_Texture", texture); //sets a uniform for the texture
    }
}