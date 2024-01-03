#ifndef TEXTURE_H
#define TEXTURE_H

#include<GL/glew.h>
#include<string>
#include "stb_image.h"


class Texture
{
public:
    Texture();
    Texture(GLenum TextureTarget, const std::string& FileName);
    bool Load();
    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
};

#endif // TEXTURE_H
