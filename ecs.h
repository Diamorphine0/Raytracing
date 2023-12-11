#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

#ifndef ECS_H
#define ECS_H

struct Vertex{
    glm::vec3 Coordinates;
    glm::vec3 Color;

    Vertex(glm::vec3 Coordinates, glm::vec3 Color){
        this->Coordinates = Coordinates;
        this->Color = Color;
    }
};

class Mesh{
public:
    std::vector<Vertex> vertices;
    Mesh(std::vector<Vertex> vertices){
        this->vertices = vertices;
        setupMesh();
    }
    void Draw(){
        glDrawArrays(GL_TRIANGLES, 0, vertices.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
    }
private:
    GLuint VAO, VBO;
    void setupMesh(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO); // vertex buffer

        //handles the VBO
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

        // vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            sizeof(Vertex),     // stride - THAT MAY BE WRONG!
            (void*)0            // array buffer offset
            );
        // colors?

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*)offsetof(Vertex, Color)                          // array buffer offset
            );

        //source: https://learnopengl.com/Model-Loading/Mesh
    }
};

/*
class Entity{
public:
    std::string Tag;
};
*/

#endif // ECS_H
