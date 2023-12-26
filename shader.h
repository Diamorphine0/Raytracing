#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#ifndef SHADER_H
#define SHADER_H

class Shader{
private:
    unsigned int m_RendererID;

    // we can implement some sort of a cache here
    GLuint compileShader(const char * vertex_file_path,const char * fragment_file_path);
    unsigned int getUniformStringLocation(const std::string& name);

public:
    Shader(const char * vertex_file_path,const char * fragment_file_path);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void setUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);

};

#endif // SHADER_H
