#ifndef ENGINECAMERA_H
#define ENGINECAMERA_H

#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

#include <shader.h>
#include <random>

#include <GLFW/glfw3native.h>

class engineCamera{
public:
    engineCamera(glm::vec3 position, float horizontalAngle, float verticalAngle, float initialFoV): position(position), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle), initialFoV(initialFoV){

        direction = glm::vec3(
            cos(verticalAngle) * sin(horizontalAngle),
            sin(verticalAngle),
            cos(verticalAngle) * cos(horizontalAngle)
            );

        right = glm::vec3(
            sin(horizontalAngle - 3.14f/2.0f),
            0,
            cos(horizontalAngle - 3.14f/2.0f)
            );

        up = glm::cross(right, direction);
    }

    glm::mat4 construct_mvp(){

        glm::mat4 Projection = glm::perspective(glm::radians(initialFoV), 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        glm::mat4 View = glm::lookAt(
            position,           // Camera is here
            position + direction, // and looks here : at the same position, plus "direction"
            up                  // Head is up (set to 0,-1,0 to look upside-down)
            );

        glm::mat4 Model = glm::mat4(1.0f);

        return Projection * View * Model;
    }

    glm::vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
};

#endif // ENGINECAMERA_H
