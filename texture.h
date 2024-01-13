#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "Entity.h" // this is just to have all the necessary files (the file structure can definetly be improved)

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
