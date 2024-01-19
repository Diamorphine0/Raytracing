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
#include "shader.h"
using namespace glm;

class Node{
public:
    Entity* entity;
public:
    Node();
    Node(Entity* entity);
    Node(Entity* entity, Node* parent);
    Node(Entity* entity, Node* parent, std::vector<Node*> children);
    ~Node();

    void setParent(Node* parent);
    void addKeyframe(float time);

    void Animate(const Shader& shader, float time, glm::vec3 pos);

    void updateWorldMatrix();
    void Draw(const Shader& shader, glm::vec3 pos); //camera position - somewhere we do need to pass it

    glm::mat4 getModelMatrix();

    bool hasChildren();
    std::vector<Node*> getChildren();
    Node* getParent();


private:
    Node* parent;
    std::vector<Node*> children;
};

#endif // SCENEGRAPH_H