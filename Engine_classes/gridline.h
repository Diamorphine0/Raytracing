#ifndef GRIDLINE_H
#define GRIDLINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "shader.h"
#include "Engine.h"

class line{
public:
    std::vector<GLfloat> segments;
    glm::mat4 model = glm::mat4(1.0f);
    GLuint vao, vbo;

    line(){
        segments = {0, 0, 0, 1, 1, 1};
        setup();
    }

    line(glm::vec3 left, glm::vec3 right){
        segments.push_back(left.x);
        segments.push_back(left.y);
        segments.push_back(left.z);
        segments.push_back(right.x);
        segments.push_back(right.y);
        segments.push_back(right.z);
        setup();
        std::cout<< "a line was generated with coordinates" << left.x<< " "<<left.y<<" "<<left.z<<" "<<right.x << " " << right.y  << " " << right.z << std::endl;
    }

    void setup(){
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * segments.size(), segments.data(), GL_STATIC_DRAW);

        // Specify the layout of the vertex data
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        std::cout<< "a line was successfully setup" << std::endl;
    }

    void draw(const Shader& shader,const Engine& engine){
        shader.Bind();
        glm::mat4 transform = engine.camera.construct_mvp() * model;
        GLuint MatrixID = glGetUniformLocation(shader.getID(), "Transform");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &transform[0][0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_LINES, 0, segments.size());
        glClear(GL_DEPTH_BUFFER_BIT);
    }
};

class grid
{
public:
    std::vector<line> lines;

    void add_line(line a){
        lines.push_back(a);
    }

    void gen_axes(GLfloat limit){
        line x = line(glm::vec3(-limit, 0, 0), glm::vec3(limit, 0, 0));
        line y = line(glm::vec3(0, -limit, 0), glm::vec3(0, limit, 0));
        line z = line(glm::vec3(0, 0, -limit), glm::vec3(0, 0, limit));

        lines.push_back(x);
        lines.push_back(y);
        lines.push_back(z);
        std::cout<<"Loaded 3 axes \n";
    }
    //just horizontal!
    void gen_big_grid(GLfloat limit, GLuint subdivisions){
        for(int i = 0; i < subdivisions; i++){
            GLfloat ratio = (-limit) * (GLfloat)i / (GLfloat)(subdivisions + 1) + (limit) * (GLfloat)(subdivisions + 1 - i) / (GLfloat)(subdivisions + 1);
            line x_aux = line(glm::vec3(-limit, 0, ratio), glm::vec3(limit, 0, ratio));
            line y_aux = line(glm::vec3(ratio, 0, -limit), glm::vec3(ratio, 0, limit));
            lines.push_back(x_aux);
            lines.push_back(y_aux);
        }

    }

    void draw(const Shader& shader,const Engine& engine){
        for(auto l : lines)
            l.draw(shader, engine);
    }
};

#endif // GRIDLINE_H
