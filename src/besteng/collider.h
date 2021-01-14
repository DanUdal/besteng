#pragma once
#include "component.h"
#include "rend/mathutil.h"
#include <vector>
#include <array>
#include <memory>

namespace besteng
{

    struct Collider : public Component //base collider class for every collider type. provides base methods and attributes for all colliders to be called
    {
    public:
        virtual glm::vec3 findFurthestPoint(glm::vec3 direction); //this calculates the most extreme point in a certain direction. used for GJK
        bool mesh; //this variable will tell the collision logic whether a mesh collision test is needed or not. if false can use shere collision
        float maxDis; //this is the furthest distance from the center to any point. it is used for the broad collision logic to improve efficiency
    };

    struct MeshCollider : public Collider
    {
    private:
        std::vector<glm::vec3> vertices; //vector containing all the vertices of the mesh
    public:
        MeshCollider() : mesh(true) //set true for a mesh hitbox
        { }
        glm::vec3 findFurthestPoint(glm::vec3 direction);
        bool mesh;
    };

    struct Simplex //class used to simplify collision functions used elsewhere
    {
    private:
        std::array<glm::vec3, 4> points; //this simplex will be 3D at most which means it requires 4 points. 1 more than the number of dimensions
        int size;
    public:
        Simplex() : points{glm::vec3(0),glm::vec3(0),glm::vec3(0),glm::vec3(0)}, size(0) //all points and the size are initialised to 0. no points are being used at first
        { }
        std::shared_ptr<Simplex> operator=(std::initializer_list<glm::vec3> list); //sets simplex equal to a list of points
        void pushFront(glm::vec3 point); //adds point to the array
        glm::vec3& operator[](int i) 
        { 
            return points[i]; //gets point at specific index
        }
        int getSize()
        {
            return size; 
        }
        auto begin()
        {
            return points.begin();
        }
        auto end() //returns iterator to beginning and end respectively
        {
            return points.end() - (4 - size);
        }
        std::weak_ptr<Simplex> self; //self pointer
    };
}