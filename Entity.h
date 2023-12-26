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
    glm::vec3 Normal;

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

private:
    // This is the VBO
    GLuint m_RendererID;
public:
    VertexBuffer(const void* data, unsigned int size);
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
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
};

// The entity gives the interface for dealing with the mesh
class Entity{

public:

    // what is the difference from a vertex buffer element
    // to every entity we provide a list of verticies that will form it
    Entity(std::vector<Vertex>& vertices);

    void rotate(){
        return ;
    }

    void translate(){
        return ;
    }

    void scale(){
        return;
    }

    void setColor(){
        return ;
    }

    inline auto getVA(){ return va;};

private:
    // there should be a shader associated to every entity
    VertexArray* va;
};

#endif
