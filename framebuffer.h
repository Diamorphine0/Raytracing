#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#pragma once
#include <iostream>
#include "Engine.h"

class FrameBuffer
{
public:
    FrameBuffer(float width, float height);
    ~FrameBuffer();
    unsigned int getFrameTexture();
    void Bind() const;
    void Unbind() const;
private:
    // stores the ID of the framebuffer object
    unsigned int fbo;
    unsigned int texture;
    // stores the ID of the renderbuffer object
    unsigned int rbo;
};

#endif // FRAMEBUFFER_H
