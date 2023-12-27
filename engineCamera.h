#ifndef ENGINECAMERA_H
#define ENGINECAMERA_H

#include "shader.h"
#include "scenegraph.h"

#include <GLFW/glfw3native.h>

class engineCamera{

public:

    void renderScene(SceneGraph* SG, const Shader& shader) const;

    // we need to pass a vertex array and a shader

    // instead of rendering the entire scene we will now just need to draw call on the highest instance object in the tree
    // (We can equally just have an "empty" world object that acts as the parent for all).
    void Draw(Entity* entity, const Shader& shader) const;

    void Clear() const{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

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

    glm::mat4 construct_mvp();

    // General Camera Control should be improved

    void movement(float& currentTime, float& lastTime, float& speed, GLFWwindow* window);

    inline glm::vec3 getPosition(){return position;};

private:
    glm::vec3 position;
    float horizontalAngle;
    float verticalAngle;
    float initialFoV;
    glm::vec3 direction;
    glm::vec3 right;
    glm::vec3 up;
};
#endif // ENGINECAMERA_H
