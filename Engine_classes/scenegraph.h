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
#include <memory>
using namespace glm;

class Node{
public:
    std::shared_ptr<Entity> entity;
public:
    Node();
    Node(const std::shared_ptr<Entity> &entity);
    Node(const std::shared_ptr<Entity> &entity, Node* parent);
    Node(const std::shared_ptr<Entity> &entity, Node* parent, const std::vector<Node*> &children);
    ~Node();

    void setParent(Node* parent);
    void addKeyframe(float time);

    void Animate(const Shader& shader, float time, glm::vec3 pos);

    void updateWorldMatrix();
    void Draw(const Shader& shader, glm::vec3 pos); //camera position - somewhere we do need to pass it

    void dfs_entitity_setup(int frame, std::vector<std::shared_ptr<Entity>> &entities, bool animate);

    glm::mat4 getModelMatrix();

    bool hasChildren();
    const std::vector<Node*>& getChildren();
    Node* getParent();


private:
    Node* parent;
    std::vector<Node*> children;
};

#endif // SCENEGRAPH_H
