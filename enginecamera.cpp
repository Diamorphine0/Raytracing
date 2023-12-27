#include "engineCamera.h"

void engineCamera::Draw(const VertexArray& va, const Shader& shader) const{

    std::cout << "Draw Function" << std::endl;
    shader.Bind();
    std::cout << "Shader Binded" << std::endl;
    va.Bind();
    std::cout << "VA Binded " << va.getID() << std::endl;
    // the size should be stored in the va ...
    glDrawArrays(GL_TRIANGLES, 0, 6);
    std::cout << "Displayed to Screen" << std::endl;
};

void engineCamera::renderScene(SceneGraph* SG, const Shader& shader) const{
    std::cout << "Render Function" << std::endl;
    std::cout << (SG -> getEntities()).size() << std::endl;
    for(auto entity: SG -> getEntities()){
        std::cout << "Draw Call to " <<  entity -> getVA() << std::endl;
        Draw(*(entity -> getVA()), shader);
    }
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
