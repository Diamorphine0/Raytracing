#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#pragma once
#include <iostream>
#include "Camera.hpp"
#include "engineCamera.h"
#include "scenegraph.h"
#include "Entity.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

class FrameBuffer
{
public:
    FrameBuffer(float width, float height);
    ~FrameBuffer();
    unsigned int getFrameTexture();
    void Bind() const;
    void Unbind() const;
    void RescaleFrameBuffer(float width, float height);
private:
    // stores the ID of the framebuffer object
    unsigned int fbo;
    unsigned int texture;
    // stores the ID of the renderbuffer object
    unsigned int rbo;
};

#endif // FRAMEBUFFER_H
