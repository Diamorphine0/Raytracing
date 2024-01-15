#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "framebuffer.h"

int main()
{

    auto rayTracingCamera = new Camera(1800, 800, Point3(0, 0, 0));
    Engine engine = Engine(1800, 800, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f));

    // for now we just store the position and color of each vertex
    // y coord

//    Vertex v1(glm::vec3(-0.995921f, 0.158561f, 1), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v2(glm::vec3(-2.99592f, 0.158561f, 1), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v3(glm::vec3( -2.99592f, 0.158561f, -1), glm::vec3(1.0f,  1.0f,  1.0f));

//    Vertex v4(glm::vec3(-2.99592f, 2.15856f, -1.f), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v5(glm::vec3(-2.99592f, 2.15856f,1.f), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v6(glm::vec3(-0.995922f, 2.15856f,1.f), glm::vec3(1.0f,  1.0f,  1.0f));

//    Vertex v7(glm::vec3(0.995921f, 2.15856f, -0.999999f), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v8(glm::vec3(-0.995921f, 0.158561f, -1.f), glm::vec3(1.0f,  1.0f,  1.0f));
//    Vertex v9(glm::vec3(-0.995921f, 0.158561f, 1.f), glm::vec3(1.0f,  1.0f,  1.0f));

//    std::vector<Vertex> vertices1{v7, v8, v9};

    // Entity instantiation

    // only a single face of the object loaded..,
    Entity* entity1 = new Entity("../Raytracing/objects/sphere.obj");
    Entity* entity2 = new Entity("../Raytracing/objects/sphere.obj");
    Entity* entity3 = new Entity("../Raytracing/objects/sphere.obj");

    entity2 -> scale(0.5, 0.5, 0.5);
    entity2 -> translate(-10, -10, 0);

    entity3 -> scale(0.4, 0.4, 0.4);
    entity3->translate(-10, -10, 0);

    Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);
    Node* node3 = new Node(entity3);

    node1 -> setParent(engine.engineWorld);
    node2 -> setParent(node1);
    node3 -> setParent(node2);

//    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
//    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.001f;

    do{
        engine.shader -> Bind();

        std::cout << "Adjust camera" << std::endl;
        // we now also want to rotate
        engine.camera.movement(currentTime, lastTime, speed, engine.window);
        std::cout << "Camera adjusted" << std::endl;

        std::cout << "Scene rendered" << std::endl;
        // adding anything to the scene graph should happen here ...
        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
