#include "collider.h"

namespace besteng
{

    glm::vec3 Collider::findFurthestPoint(glm::vec3 direction)
    {

    }

    glm::vec3 MeshCollider::findFurthestPoint(glm::vec3 direction)
    {
        glm::vec3 maxPoint;
        float maxDistance = -FLT_MAX; //sets the initial test variable to the negative maximum of a float so the first test will always find 1 distance
        for (auto it = vertices.begin(); it < vertices.end(); it++) //iterates through the vertices
        {
            float distance = glm::dot(*(it), direction);
            if (distance > maxDistance) //calculates the distance to the vertex in the direction specified and if it's the highest so far set it as the return value 
            {
                maxDistance = distance;
                maxPoint = *it;
            }
        }
        return maxPoint;
    }

    std::shared_ptr<Simplex> Simplex::operator=(std::initializer_list<glm::vec3> list) //sets each point to the corresponding point in the list and returns pointer to simplex
    {
        for (auto v = list.begin(); v < list.end(); v++)
        {
            points[std::distance(list.begin(), v)] = *v;
        }
        size = list.size();
        return self.lock();
    }

}