#include "engineCamera.h"

engineCamera::engineCamera(glm::vec3 position, float horizontalAngle, float verticalAngle, float initialFoV): position(position), horizontalAngle(horizontalAngle), verticalAngle(verticalAngle), initialFoV(initialFoV){

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
    engineWorld -> Draw(shader);
};

void engineCamera::movement(float& currentTime, float& lastTime, float& speed, GLFWwindow* window){

    lastTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }

    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }
}

glm::mat4 engineCamera::construct_mvp(){

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
