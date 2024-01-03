#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

//for debugging
#include <iostream>
// for .obj model reading
#include <fstream>

#include "texture.h"
#include "Utilities.hpp"

#ifndef ECS_H
#define ECS_H

// more difficult to deal with a struct

struct Vertex {
    glm::vec3 coordinates;
    glm::vec2 uv;
    glm::vec3 normals;
    glm::vec3 colors;
};

/*static unsigned int GetSizeOfType(unsigned int type){
    switch(type){
    case GL_FLOAT: return 4;
    case GL_UNSIGNED_INT: return 4;
    case GL_UNSIGNED_BYTE: return 1;
    }
    return 0;
}*/

// The entity gives the interface for dealing with the mesh
class Entity{

public:
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    glm::mat4 localMatrix = glm::mat4(1.0f);

    std::vector<Vertex> mesh;
    Texture* pTexture = nullptr;
    GLuint gSamplerLocation;
    //for setup
    GLuint VAO, VBO;

public:
    Entity() : gSamplerLocation(0), VAO(0), VBO(0) {}

    Entity(const char* path); //loaded from file

    void loadOBJ(const char* path);

    void setup();

    void addTexture(const char* path);

    void addColor();

    void printOBJToFile(const std::string& filename);

    inline void rotate(float speed, float x, float y, float z){ localMatrix = glm::rotate(localMatrix, speed, glm::vec3(x, y, z));};

    inline void translate(float dx, float dy, float dz){localMatrix = glm::translate(localMatrix, glm::vec3(dx, dy, dz));};

    inline void scale(float dx, float dy, float dz){localMatrix = glm::scale(localMatrix, glm::vec3(dx, dy, dz));};

    //inline void setColor(glm::vec3 Color){ return ;};

};

#endif
