#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string& path):
    filePath(path), localBuffer(nullptr), width(0), height(0), bitsPerPixel(0)
{
    constant_color = false;
    stbi_set_flip_vertically_on_load(1);
    // we are loading to a local buffer
    localBuffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 3);
    // check if the image was actually laoded ?

    if(localBuffer){
//        std::cout << "We get data" << std::endl;
    }else{
        std::cout << "Cannot read texture" << std::endl;
        if(stbi_failure_reason())
            std::cout << "Error Reason:" << stbi_failure_reason() << std::endl;

        localBuffer = stbi_load((SOURCE_DIR + std::string("textures/Grey.png")).c_str(), &width, &height, &bitsPerPixel, 3);
    }

    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // we load the tex image to a local buffer
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, localBuffer);
    glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::Texture(const color3 &col) {
    constant_color = true;
    color = col;
}

Texture::~Texture(){
    stbi_image_free(localBuffer);
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

color3 Texture::get_color_coordinates(double u, double v) const {
    if(constant_color)
        return color;
    u = u - std::floor(u);
    v = v - std::floor(v);

    int x = static_cast<int>(u * width);
    int y = static_cast<int>(v * height);

    x = glm::clamp(x, 0, width - 1);
    y = glm::clamp(y, 0, height - 1);

    int index = (y * width + x) * 3;

    unsigned char r = localBuffer[index];
    unsigned char g = localBuffer[index + 1];
    unsigned char b = localBuffer[index + 2];

    return glm::vec3((float)r/255.999f, (float)g/255.999f, (float)b/255.999f);
}
