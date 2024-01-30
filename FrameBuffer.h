#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>
#include <iostream>

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

class frameBuffer
{
public:
    GLuint m_RendererID;
    GLuint texture_id;
    // this should not be called like this,
    GLuint RBO;
    // should be passed as parameters and retrieved from the engine entity;
    float width, height;
public:
    frameBuffer(float width, float height);
    void Bind();
    void BindData(std::vector<std::vector<glm::vec<3, float>>>* data);
    void Unbind();
    void Rescale(float width, float height);
};

#endif // FRAMEBUFFER_H
