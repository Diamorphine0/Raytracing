#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "Metal.h"
int main()
{
    //auto rayTracingCamera = new Camera(1024, 768, Point3(0, 0, 0));
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f));


    // Entity instantiation

    // only a single face of the object loaded..,
//    Entity* entity1 = new Entity("../objects/sphere.obj");
//    entity1->translate(3, 3, 1);

    Entity* entity2 = new Entity("../objects/cube.obj");
//    Entity* entity3 = new Entity("../objects/sphere.obj");

//    entity2 -> scale(0.5, 0.5, 0.5);
//    entity2 -> translate(-10, -10, 0);
//
//    entity3 -> scale(0.4, 0.4, 0.4);
//    entity3->translate(-10, -10, 0);

    //Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);

//    Node* node3 = new Node(entity3);

    //std::cout << "Size" << engine.engineWorld -> entity -> hl -> objects_list.size() << std::endl;

    //node1 -> setParent(engine.engineWorld);
    node2 -> setParent(engine.engineWorld);
//    node2 -> setParent(node1);
//
//    node3 -> setParent(node2);

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.001f;

    Shader shader("../vertexshader.shader", "../fragmentshader.shader");

    do{
        shader.Bind();

        //std::cout << "Adjust camera" << std::endl;
        // we now also want to rotate
        //engine.camera.movement(currentTime, lastTime, speed, engine.window);
        //std::cout << "Camera adjusted" << std::endl;

        engine.camera.renderScene(engine.engineWorld, shader);
        //std::cout << "Scene rendered" << std::endl;
        // adding anything to the scene graph should happen here ...
        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
