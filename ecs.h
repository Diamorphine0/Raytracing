#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
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

// the mesh should likewise contain the color and texture and normals
class Mesh{

public:
    std::vector<Vertex> vertices;

    // We should likewise include the textures.
    // We should likewise include the indicies.

    Mesh(std::vector<Vertex> vertices){
        this->vertices = vertices;
        setupMesh();
    }

    void Draw(){

        // glBindVertexArray -> bind it to a VAO;

        // glDrawElements -> draw the object;

        // we need to set a uniform everytime

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    }

    //rotates the vertices, stores in same object
    void rotate_mesh(glm::vec3 rot_axis, float angle){
        rot_axis = glm::normalize(rot_axis);
        glm::quat rot_quat(cos(angle/2), rot_axis.x*sin(angle/2), rot_axis.y*sin(angle/2), rot_axis.z*sin(angle/2));

        //store position of rotated vertex in place, and keeps same color
        for (int i=0; i<vertices.size(); i++){
            Vertex v = vertices[i];
            glm::quat position_quat(0, v.Coordinates.x, v.Coordinates.y, v.Coordinates.z);
            glm::quat rot_pos_quat = rot_quat*position_quat*glm::conjugate(rot_quat);


            glm::vec3 rot_coord(rot_pos_quat.x, rot_pos_quat.y,rot_pos_quat.z);
            Vertex rot_v(rot_coord, v.Color);

            vertices[i] = rot_v;
        }
        setupMesh();        //Given list of rotated vertices, reset mesh to be rotated mesh
    }

private:

    // should contain a bounding box

    GLuint VAO, VBO;

    // we should be setting up a mesh for a single object

    void setupMesh(){
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

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

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*)offsetof(Vertex, Color)                          // array buffer offset
            );

    }

};

// The object should have a rotation

class pointLightSource{

private:
    // do we need anything else for a light source;
    // we need to store a position;
};

class Object{

public:

    Object(Mesh* mesh){
        return ;
    }

    // how does object picking work ? - we want to be able to pick an object

    void render(){
        // Do we need to do anything past
        return ;
    }

    void rotate(){
        return ;
    }

    void move(){
        return ;
    }

    void setColor(){
        return ;
    }

private:

    Mesh* mesh;

};

#endif // ECS_H

