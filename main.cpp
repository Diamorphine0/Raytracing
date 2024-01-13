#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"

int main()
{

    auto rayTracingCamera = new Camera(1024, 768, Point3(0, 0, 0));
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f));

    // only a single face of the object loaded..,
    Entity* entity1 = new Entity("../Raytracing/objects/cube.obj");
    Entity* entity2 = new Entity("../Raytracing/objects/cube.obj");
    Entity* entity3 = new Entity("../Raytracing/objects/cube.obj");

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

    Shader shader("../Raytracing/vertexshader.shader", "../Raytracing/fragmentshader.shader");

    do{
        shader.Bind();
        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        // the render scene and animate scene functionalities should be disjoint.
        engine.camera.renderScene(engine.engineWorld, shader);
        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
