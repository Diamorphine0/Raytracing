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
#include "Dielectric_Material.h"

int main(int argc, char* argv[])
{

    Engine engine = Engine(engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f), SOURCE_DIR + (std::string)"/shaders");

    // only a single face of the object loaded..,
    auto entity1 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cube.obj");
    entity1->material = std::make_shared<Dielectric>(0.9, 1);
    auto entity2 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cone.obj");
    entity2->translate(-5, -5, 5);
    // to get the object identifier we can just count hte total number of objects stored in the scene grap

    Lightarray lights;
    Lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

    engine.engineWorld -> setName("Scene Graph Root (Engine Camera)");
//    grid big_grid;
//    big_grid.gen_big_grid(1000, 501);
//
//    grid axes;
//    axes.gen_axes(1000);

    entity1 -> texture = std::make_shared<Texture>(SOURCE_DIR + (std::string)"/Textures/earth.png");

    std::cout << "Texture is loaded" << std::endl;
//    auto entity2 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/frog.obj");
//    auto entity3 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cube.obj");
//
  //  entity2 -> texture = std::make_shared<Texture>(SOURCE_DIR + (std::string)"/Textures/purple.png");
//
//    entity2 -> scale(0.5, 0.5, 0.5);
//    entity2 -> translate(-10, -10, 0);
//
//    entity3 -> scale(0.4, 0.4, 0.4);
//    entity3->translate(-10, -10, 0);

    Node* node1 = new Node(entity1);
  //  Node* node2 = new Node(entity2);
//    Node* node2 = new Node(entity2);
//    Node* node3 = new Node(entity3);

    node1 -> setParent(engine.engineWorld);
 //   node2 ->setParent(engine.engineWorld);
    engine.engineWorld ->addKeyframe(0);

    //entity1 -> scale(0.1, 0.1, 0.1);
    //entity1 -> rotate(1, 2, 3, 4);

    engine.engineWorld ->addKeyframe(2000);

//    engine.engineWorld -> addKeyframe(300);
//
//    entity1 -> translate(5, 5, 1);
//
//    engine.engineWorld -> addKeyframe(600);
//
//    entity1 -> scale(10, 2, 1);
//
//    engine.engineWorld -> addKeyframe(600);

    //setting the names so that they are displayed on the display on the left hand side
    node1 -> setName("frogsterfrogginson");
   // node2 -> setName("aliensBuiltThePyramids");

    float currentTime = glfwGetTime();
    float lastTime = currentTime;

    float speed = 5.0f;

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
