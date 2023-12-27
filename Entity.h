#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#ifndef ECS_H
#define ECS_H

// more difficult to deal with a struct
struct Vertex{
    glm::vec3 Coordinates;
    glm::vec3 Color;

    Vertex(glm::vec3 Coordinates, glm::vec3 Color){
        this->Coordinates = Coordinates;
        this->Color = Color;
    }
};

// Stores information about a single instance of the vertex struct
struct VertexBufferElement{

    unsigned int type;
    unsigned int count;
    bool normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch(type){
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
            case GL_UNSIGNED_BYTE: return 1;
        }
        return 0;
    };

};

// This is equivalent to storing a vertex mesh
class VertexBuffer{

public:
    // This is the VBO
    GLuint m_RendererID;

    VertexBuffer(const void* data, unsigned long size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;
};

class VertexBufferLayout{

private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;

public:
    VertexBufferLayout()
        :m_Stride(0){}

    template<typename T>
    void Push(unsigned int count){
    }

    template<> void Push<float>(unsigned int count){
        m_Elements.push_back({ GL_FLOAT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    template<> void Push<unsigned int>(unsigned int count){
        m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    template<> void Push<Vertex>(unsigned int count){
        m_Elements.push_back({ GL_FLOAT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    // we want to create a template for a more complex vertex containing both position and color

    inline const std::vector<VertexBufferElement> GetElements() const {return m_Elements;};
    inline unsigned int getStride() const {return m_Stride;};
};

class VertexArray{
private:
    unsigned int m_RendererID;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;
    void AddBuffer(const VertexBuffer* vb, const VertexBufferLayout& layout);
    inline unsigned int getID() const{return m_RendererID;};
};

// The entity gives the interface for dealing with the mesh
class Entity{

public:
    glm::mat4 worldMatrix = glm::mat4(1.0f);
public:

    // what is the difference from a vertex buffer element
    // to every entity we provide a list of verticies that will form it
    Entity(std::vector<Vertex>& vertices);

    void rotate(float x, float y, float z){
        worldMatrix = glm::rotate(worldMatrix, 0.05f, glm::vec3(x, y, z));
    }

    void translate(float dx, float dy, float dz){
        worldMatrix = glm::translate(worldMatrix, glm::vec3(dx, dy, dz));
    }

    void scale(float dx, float dy, float dz){
        worldMatrix = glm::scale(worldMatrix, glm::vec3(0.999, 0.999, 0.0));
    }

    void setColor(glm::vec3 Color){
        return ;
    }

    inline auto getVA(){ return va;};

private:
    VertexArray* va;
    // should contain a world matrix - what is the difference between
};

#endif
