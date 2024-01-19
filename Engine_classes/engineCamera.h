#ifndef ENGINECAMERA_H
#define ENGINECAMERA_H

#include "shader.h"
#include "scenegraph.h"

#include <GLFW/glfw3native.h>

class engineCamera{

public:

    engineCamera(glm::vec3 position, float horizontalAngle, float verticalAngle, float initialFoV);

    void renderScene(Node* SG, const Shader& shader);
    void animateScene(Node* engineWorld, const Shader& shader, float& timeStamp, float timeDelta);

    inline void Clear() const{ glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);};

    glm::mat4 construct_mvp() const;

    void movement(float& currentTime, float& lastTime, float& speed, GLFWwindow* window);

    inline glm::vec3 getPosition(){return position;};

private:
    GLFWwindow* window;
    double xpos, ypos;
    float mousespeed = 0.0025f;
    glm::vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
};
#endif // ENGINECAMERA_H