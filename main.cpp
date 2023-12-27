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

    // initialize a scene graph ?
    SceneGraph* SG = new SceneGraph();

    // for now we just store the position and color of each vertex
    Vertex v1(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.609f,  0.115f,  0.436f));
    Vertex v2(glm::vec3(1.0f,-1.0f, -1.0f), glm::vec3(0.609f,  0.115f,  0.436f));
    Vertex v3(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.609f,  0.115f,  0.436f));
    Vertex v4(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v5(glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v6(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    std::vector<Vertex> vertices{v1, v2, v3, v4, v5, v6};

    std::cout << "Size" << vertices.size() << std::endl;
    std::cout << "We get here!!!" << std::endl;

    // Entity instantiation

    Entity* entity1 = new Entity(vertices);

    // this should be a template
    SG -> addEntity(entity1);

    std::cout << (entity1 -> getVA()) << std::endl;

    std::cout << "Size" << (SG -> getEntities()).size() << std::endl;

    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.005f;

    Shader shader("../vertexshader.shader", "../fragmentshader.shader");

    std::cout << GL_FLOAT << " "<< sizeof(Vertex) << std::endl;

    do{
        engine.camera.Clear();

        shader.Bind();

        engine.camera.renderScene(SG, shader);

        glDrawArrays(GL_TRIANGLES, 0, vertices.size());

        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
