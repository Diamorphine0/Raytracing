#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "lightsource.h"
#include <string>
#include "BVH_Node.h"

int main(int argc, char* argv[])
{

    Engine engine = Engine(engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f), SOURCE_DIR + (std::string)"/shaders");

    // only a single face of the object loaded..,
    auto entity1 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cube.obj");

    auto entity2 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cone.obj");
    entity2->translate(-5, -5, 5);
    // to get the object identifier we can just count hte total number of objects stored in the scene grap

    Lightarray lights;
    Lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

    entity1 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/Grey.png");

    std::cout << "Texture is loaded" << std::endl;
    entity2 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/Grey.png");

    Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);

    node1 -> setParent(engine.engineWorld);
    node2 ->setParent(engine.engineWorld);
    engine.engineWorld -> setName("root");

    //setting the names so that they are displayed on the display on the left hand side
    node1 -> setName("frogsterfrogginson");
    node2 -> setName("aliensBuiltThePyramids");

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.01f;

    Shader* shader = new Shader(SOURCE_DIR + (std::string)"/shaders/vertexshader.shader", SOURCE_DIR + (std::string) "/shaders/fragmentshader.shader");

    float animationTime = 0;

    do{
       shader -> Bind();

        //this should handle light loading
        for(int i = 0; i < 20; i++){

            std::string istring = "lights[" + std::to_string(i) + "].lightPos";
            const char* annoying = istring.c_str();
            GLuint lightPosi = glGetUniformLocation(shader -> getID(), annoying);

            istring = "lights[" + std::to_string(i) + "].lightColor";
            annoying = istring.c_str();
            GLuint lightColori = glGetUniformLocation(shader -> getID(), annoying);

            glUniform3fv(lightPosi, 1, &lights.arr[i].lightPos[0]);
            glUniform3fv(lightColori, 1, &lights.arr[i].lightColor[0]);
        }

        std::cout << currentTime << std::endl;
        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        engine.update(shader);
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
