#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include<bits/stdc++.h>
#include<shader.h>

#ifndef ECS_H
#define ECS_H

using Entity = std::size_t;

struct Vertex{
    glm::vec3 Coordinates;
    glm::vec3 ColorCoordinates;

    Vertex(glm::vec3 Coordinates, glm::vec3 ColorCoordinates){
        this->Coordinates = Coordinates;
        this->ColorCoordinates = ColorCoordinates;
    }
};

class Mesh{
public:
    std::vector<float> coordinates;
    std::vector<float> colorcoordinates;
    GLuint VAO, VBO, CBO;

    Mesh(){}
    Mesh(std::vector<Vertex> verts){
        for(auto v : verts){
            coordinates.push_back(v.Coordinates.x);
            coordinates.push_back(v.Coordinates.y);
            coordinates.push_back(v.Coordinates.z);

            colorcoordinates.push_back(v.ColorCoordinates.x);
            colorcoordinates.push_back(v.ColorCoordinates.y);
            colorcoordinates.push_back(v.ColorCoordinates.z);
        }
        setupMesh();
    }
    void Draw(){
        GLuint programID = LoadShaders( "vertexshader.shader", "fragmentshader.shader" );
        glUseProgram(programID);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride - THAT MAY BE WRONG!
            (void*)0            // array buffer offset
            );
        // colors?

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, CBO);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,//sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*)0                          // array buffer offset
            );
        glDrawArrays(GL_TRIANGLES, 0, coordinates.size()); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);
    }

    void setupMesh(){
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(float), &coordinates, GL_STATIC_DRAW);

        //handles the CBO
        glGenBuffers(1, &CBO);
        glBindBuffer(GL_ARRAY_BUFFER, CBO);
        glBufferData(GL_ARRAY_BUFFER, colorcoordinates.size() * sizeof(float), &colorcoordinates, GL_STATIC_DRAW);

        // vertex positions

        //source: https://learnopengl.com/Model-Loading/Mesh
    }
};

class Registry{
public:
    std::unordered_map<Entity, Mesh> meshes; //for now, the only component
};

//should render everything
class RenderSystem{
public:
    void update(Registry& registry, Entity& max_entity){
        for(Entity tag = 0; tag <= max_entity; tag++){
            if(registry.meshes.find(tag) != registry.meshes.end()){
                registry.meshes[tag].Draw();
            }
        }
    }
};

class ecs{
public:
    Entity max_entity = -1;
    Registry registry;
    RenderSystem rendersystem;
    //for now all entities are meshes

    void AddEntity(Mesh mesh){
        max_entity++;
        registry.meshes[max_entity] = mesh;
    }

    void update(){
        rendersystem.update(registry, max_entity);
    }
};


#endif // ECS_H
