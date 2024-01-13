#include "texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path):
    filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)
{

    stbi_set_flip_vertically_on_load(1);
    // we are loading to a local buffer
    localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
    // check if the image was actually laoded ?

    if(localBuffer){
//        std::cout << "We get data" << std::endl;
    }else{
        std::cout << "Cannot read texture" << std::endl;
        if(stbi_failure_reason())
            std::cout << "Error Reason:" << stbi_failure_reason() << std::endl;
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // we load the tex image to a local buffer
    glTexImage2D(GL_TEXTURE_2D, 1, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
//    stbi_image_free(localBuffer);
}

Texture::~Texture(){
    glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind() const{
    glActiveTexture(GL_TEXTURE);
    // it suffices to use the m_RendererID
    glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}
