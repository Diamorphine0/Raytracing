#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

//for debugging
#include <iostream>
// for .obj model reading
#include <fstream>

#ifndef ECS_H
#define ECS_H

// more difficult to deal with a struct
struct Vertex{

    glm::vec3 Coordinates;
    glm::vec3 Color;
    // a single vertex cannot have a normal associated to it ...

    Vertex(glm::vec3 Coordinates, glm::vec3 Color){
        this->Coordinates = Coordinates;
        this->Color = Color;
    }
};

// we should have a mesh object - what the verticies is doing right now ...

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

   void Push_float(unsigned int count){
        m_Elements.push_back({ GL_FLOAT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

    void Push_int(unsigned int count){
        m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }

    void Push_Vertex(unsigned int count){
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
    glm::mat4 localMatrix = glm::mat4(1.0f);
    std::vector<Vertex> vertices;
public:

    Entity();

    Entity(const char* path);

    Entity(std::vector<Vertex>& vertices);

    inline void rotate(float speed, float x, float y, float z){ localMatrix = glm::rotate(localMatrix, speed, glm::vec3(x, y, z));};

    inline void translate(float dx, float dy, float dz){localMatrix = glm::translate(localMatrix, glm::vec3(dx, dy, dz));};

    inline void scale(float dx, float dy, float dz){localMatrix = glm::scale(localMatrix, glm::vec3(dx, dy, dz));};

    inline void setColor(glm::vec3 Color){ return ;};

    inline auto getVA(){ return va;};

    bool loadOBJ(
        const char* path,
        std::vector < Vertex >& out_vertices,
        std::vector < glm::vec2 >& out_uvs,
        std::vector < glm::vec3 >& out_normals
    );

private:
    // the va should likewise include the normals & we should create an index buffer
    VertexArray* va;
};

#endif
