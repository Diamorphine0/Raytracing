#pragma once

#ifndef SCENEGRAPH_H
#define SCENEGRAPH_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include "Entity.h"
using namespace glm;

class SceneGraph{
public:
    SceneGraph();
    ~SceneGraph();
    inline void addEntity(Entity* entity){Entities.push_back(entity);};
    inline std::vector<Entity*> getEntities(){return Entities;};
private:
    std::vector<Entity*> Entities;
};

class Node{
public:

    Node();

    void setParent(){

    }

    void updateWorldMatrix(){

    }

private:
    glm::vec4 localMatrix;
    glm::vec4 worldMatrix;
    std::vector<Node> children;
    Entity thingToDraw;
};

#endif // SCENEGRAPH_H
