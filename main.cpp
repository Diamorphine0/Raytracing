#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "lightsource.h"
#include "gridline.h"
#include <string>

int main(int argc, char* argv[])
{

    auto rayTracingCamera = new Camera(1024, 768, point3(0, 0, 0));
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f));

    // only a single face of the object loaded..,
    Entity* entity1 = new Entity(SOURCE_DIR + (std::string)"/objects/sphere.obj");

    // to get the object identifier we can just count hte total number of objects stored in the scene grap

    lightarray lights;
    lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

    grid axes;
    axes.gen_axes(100);

    entity1 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/sun.png");

    std::cout << "Texture is loaded" << std::endl;
    Entity* entity2 = new Entity(SOURCE_DIR + (std::string)"/objects/earth.obj");
    Entity* entity3 = new Entity(SOURCE_DIR + (std::string)"/objects/cube.obj");

    entity2 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/purple.png");

    entity2 -> scale(0.5, 0.5, 0.5);
    entity2 -> translate(-10, -10, 0);

    entity3 -> scale(0.4, 0.4, 0.4);
    entity3->translate(-10, -10, 0);

    Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);
    Node* node3 = new Node(entity3);

    node1 -> setParent(engine.engineWorld);
    node2 -> setParent(node1);
//    node3 -> setParent(node2);*/

//    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
//    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.01f;

    Shader shader(SOURCE_DIR + (std::string)"/shaders/vertexshader.shader", SOURCE_DIR + (std::string)"/shaders/fragmentshader.shader");
    Shader shaderLine(SOURCE_DIR + (std::string)"/shaders/vertexshaderLine.shader",SOURCE_DIR + (std::string) "/shaders/fragmentshaderLine.shader");

    do{
        shader.Bind();

        //this should handle lighting loading
        for(int i = 0; i < 20; i++){

            std::string istring = "lights[" + std::to_string(i) + "].lightPos";
            const char* annoying = istring.c_str();
            GLuint lightPosi = glGetUniformLocation(shader.getID(), annoying);

            istring = "lights[" + std::to_string(i) + "].lightColor";
            annoying = istring.c_str();
            GLuint lightColori = glGetUniformLocation(shader.getID(), annoying);

            glUniform3fv(lightPosi, 1, &lights.arr[i].lightPos[0]);
            glUniform3fv(lightColori, 1, &lights.arr[i].lightColor[0]);
            //cannot initialize a parameter of type const GLfloat with an rvalue of typue glm::vec3

        }

        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        // the render scene and animate scene functionalities should be disjoint.
        engine.camera.renderScene(engine.engineWorld, shader);
        shader.Unbind();

        /*shaderLine.Bind();
        axes.draw(shaderLine, engine);
        shaderLine.Unbind();
        */
        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
