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
    std::string name;
public:
    Node();
    Node(const std::shared_ptr<Entity> &entity);
    Node(const std::shared_ptr<Entity> &entity, Node* parent);
    Node(const std::shared_ptr<Entity> &entity, Node* parent, const std::vector<Node*> &children);
    ~Node();

    void setParent(Node* parent);
    void addKeyframe(int time);
    void setName(std::string name){this->name = name;}

    void Animate(const Shader& shader, int time);

    void updateWorldMatrix();
    void Draw(const Shader& shader, glm::vec3 pos, int& currentFrame);

    void dfs_entitity_setup(int frame, std::vector<std::shared_ptr<Entity>> &entities);

    glm::mat4 getModelMatrix();

    bool hasChildren();
    std::vector<Node*> getChildren(){return children;}
    Node* getParent();

    int DFS();

private:
    Node* parent;
    std::vector<Node*> children;
};

#endif // SCENEGRAPH_H
