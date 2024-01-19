#include "engineCamera.h"
#include <math.h>

engineCamera::engineCamera(glm::vec3 position, float horizontalAngle, float verticalAngle, float initialFoV):  position(position), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle), initialFoV(initialFoV){

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

void engineCamera::renderScene(Node* engineWorld, const Shader& shader){
    Clear();

    auto mvp = construct_mvp();

    engineWorld -> entity -> worldMatrix = mvp * engineWorld -> entity -> localMatrix;

    glm::vec3 pos = getPosition();
    engineWorld -> Draw(shader, pos);
};

void engineCamera::animateScene(Node* engineWorld, const Shader& shader, float& timeStamp, float timeDelta){
    Clear();

    auto mvp = construct_mvp();

    // this should technically also time dependent
    engineWorld -> entity -> worldMatrix = mvp * engineWorld -> entity -> localMatrix;

    glm::vec3 pos = getPosition();
    engineWorld -> Animate(shader, timeStamp, pos);
    timeStamp += timeDelta;
};

// we should have an animation function here and set the delta time to basically know how often we should call the function
// or how precise we want to make the interpolation

void engineCamera::movement(float& currentTime, float& lastTime, float& speed, GLFWwindow* window){

    lastTime = glfwGetTime();

    float verticalAngleLimit = glm::radians(89.0f);
    float deltaTime = float(currentTime - lastTime);

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        horizontalAngle += mousespeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        horizontalAngle -= mousespeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        verticalAngle += mousespeed * deltaTime;
        verticalAngle = glm::clamp(verticalAngle, -verticalAngleLimit, verticalAngleLimit);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        verticalAngle -= mousespeed * deltaTime;
        verticalAngle = glm::clamp(verticalAngle, -verticalAngleLimit, verticalAngleLimit);
    }

    //z jakiegoś powodu sie tego nie da zroboc

    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    glm::vec3 left = cross(glm::vec3(0.0f, 1.0f, 0.0f), direction);
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position += left * deltaTime * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position -= left * deltaTime * speed;
    }
}

glm::mat4 engineCamera::construct_mvp() const{

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
