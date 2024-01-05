#include "engineCamera.h"

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

    std::cout << engineWorld -> entity << std::endl;
    engineWorld -> entity -> worldMatrix = mvp * engineWorld -> entity -> localMatrix;

    engineWorld -> Draw(shader);
};

void engineCamera::movement(float& currentTime, float& lastTime, float& speed, GLFWwindow* window){

    lastTime = glfwGetTime();

    float deltaTime = float(currentTime - lastTime);

//    auto x_prev = xpos;
//    auto y_prev = ypos;

//     we want to adjust some shit
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwSetCursorPos(window, 1024/2, 768/2);

    std::cout << "Change" << float(1024/2 - xpos ) << std::endl;
    std::cout << "Change" << float(768/2 - ypos ) << std::endl;

    horizontalAngle += mousespeed * deltaTime * float(1024/2 - xpos );
    verticalAngle   += mousespeed * deltaTime * float(768/2 - ypos );

    direction = glm::vec3(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
        );

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        // we want to simulate movement in a circle
        position += direction * deltaTime * speed;
//        verticalAngle+= 0.001f;

    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
//        verticalAngle-= 0.001f;
    }

    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        position -= right * deltaTime * speed;
//        horizontalAngle+= 0.001f;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        position += right * deltaTime * speed;
//        horizontalAngle-= 0.001f;
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
