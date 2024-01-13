#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#include <iostream>

class Texture
{
public:
    unsigned int m_RendererID;
    std::string filePath;
    unsigned char* localBuffer;
    int width, height, bitsPerPixel;

public:
    Texture(const std::string& path);
    ~Texture();

    void Bind() const;
    void Unbind();
};

#endif // TEXTURE_H
