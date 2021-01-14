#include "mesh.h"

namespace besteng
{
    void Mesh::initialise(std::string path)
    {
        std::string fileStr;
        std::fstream file(path, std::fstream::in);
        file >> fileStr;
        file.close();
        mesh = std::make_shared<rend::Mesh>();
        mesh->parse(fileStr);
        //scale();
    }

    void Mesh::scale()
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
    }

    void Mesh::addTexture(char* path)
    {
        texture = std::make_shared<rend::Texture>();
        unsigned char* fileStr;
        int x, y, n;
        fileStr = stbi_load(path, &x, &y, &n, 0);
        if (fileStr != NULL)
        {
            for (int yPos; yPos < y; yPos++)
            {
                for (int i = 0, int xPos; xPos < x; i + n, xPos++)
                {
                    if (n == 3)
                    {
                        texture->setPixel(xPos, yPos, glm::vec3(fileStr[i] - '0', fileStr[i + 1] - '0', fileStr[i + 2] - '0'));
                    }
                    if (n == 4)
                    {
                        texture->setPixel(xPos, yPos, glm::vec4(fileStr[i] - '0', fileStr[i + 1] - '0', fileStr[i + 2] - '0', fileStr[i + 3] - '0'));
                    }
                }
            }
        }
        mesh->setTexture("u_Texture", texture);
    }
}