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
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 0 ), 3.14f, 0.0f, 90.0f));

    // for now we just store the position and color of each vertex
    // y coord
    Vertex v1(glm::vec3(-0.1f, 0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));
    Vertex v2(glm::vec3(-0.1f, -0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));
    Vertex v3(glm::vec3( 0.1f, -0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));

    Vertex v4(glm::vec3( 0.1f, -0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));
    Vertex v5(glm::vec3(0.1f, 0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));
    Vertex v6(glm::vec3(-0.1f, 0.1f,0.00f), glm::vec3(1.0f,  1.0f,  1.0f));

    std::vector<Vertex> vertices1{v1,v2,v3,v4,v5,v6};

    // Entity instantiation

    Entity* entity1 = new Entity(vertices1);
    Entity* entity2 = new Entity(vertices1);
    Entity* entity3 = new Entity(vertices1);

    entity2 -> scale(0.5, 0.5, 1);
    entity2 -> translate(-0.7, -0.7, 0);

    entity3 -> scale(0.5, 0.5, 1);
    entity3->translate(-0.5, -0.5, 0);

    Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);
    Node* node3 = new Node(entity3);

    node1 -> setParent(engine.engineWorld);
    node2 -> setParent(node1);
    node3 -> setParent(node2);

    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.005f;

    Shader shader("../vertexshader.shader", "../fragmentshader.shader");

    do{
        shader.Bind();

        engine.camera.renderScene(engine.engineWorld, shader);

        // adding anything to the scene graph should happen here ...
        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
