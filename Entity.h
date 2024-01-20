#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/transform.hpp>

#include <vector>
#include <map>
#include "texture.h"
#include "lightsource.h"
#include <limits.h>

//for debugging
#include <iostream>
// for .obj model reading
#include <fstream>
#include <string>

#ifndef ECS_H
#define ECS_H

// more difficult to deal with a struct
struct Vertex{

    glm::vec3 Coordinates;
    glm::vec3 Color;
    glm::vec2 UV;
    glm::vec3 Norm;

    Vertex(glm::vec3 Coordinates, glm::vec3 Color): Coordinates(Coordinates), Color(Color){}
    Vertex(glm::vec3 Coordinates, glm::vec3 Color, glm::vec2 UV): Coordinates(Coordinates), Color(Color), UV(UV){}
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
        // so we push back a float ? - how would this work ?
        m_Elements.push_back({ GL_FLOAT, count, false });
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }

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

    // there is not much of a point in keeping the localMatrix
    glm::mat4 localMatrix = glm::mat4(1.0f);

    // this might lead to certain problems
    std::vector<std::pair<int, glm::mat4>> keyFrames;

    std::vector<Vertex> vertices;
    // we should store a texture pointer this way we can just load the texture
    Texture* texture = nullptr;
    Lightsource* lightsource;

    int keyFrameInitialTime = INT_MAX;
    float keyFrameFinalTime = 0;

public:

    Entity();

    Entity(std::string path);

    Entity(std::vector<Vertex>& vertices);

    void bindlightsource(Lightsource lightsource){this->lightsource = &lightsource;}

    void interpolate(int currentFrame);

    inline void rotate(float speed, float x, float y, float z){ localMatrix = glm::rotate(localMatrix, speed, glm::vec3(x, y, z)); };

    inline void translate(float dx, float dy, float dz){localMatrix = glm::translate(localMatrix, glm::vec3(dx, dy, dz));};

    inline void scale(float dx, float dy, float dz){localMatrix = glm::scale(localMatrix, glm::vec3(dx, dy, dz));};

    inline void setColor(glm::vec3 Color){ return ;};

    inline auto getVA(){ return va;};

    bool loadOBJ(
        std::string path,
        std::vector < Vertex >& out_vertices,
        std::vector < glm::vec2 >& out_uvs,
        std::vector < glm::vec3 >& out_normals
    );

    int index(int searchTime, int startIndex, int endIndex){

        if( startIndex == endIndex )
            return keyFrames[startIndex].first <= searchTime ? startIndex : -1;

        int mid_idx = startIndex + (endIndex - startIndex) / 2;

        if( searchTime < keyFrames[mid_idx].first)
            return index(searchTime, startIndex, mid_idx);

        int ret = index(searchTime, mid_idx+1, endIndex);
        return ret == -1 ? mid_idx : ret;
    };

private:
    // the va should likewise include the normals & we should create an index buffer
    VertexArray* va;
};

#endif
