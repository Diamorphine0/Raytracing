#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "engine.h"
#include "ecs.h"
#include "Camera.hpp"
#include "Triangle.h"

int main()
{
    std::cerr<<"TEST1\n";


    std::cerr<<"TEST\n";

    auto rayTracingCamera = new Camera(1024, 768, Point3(0, 0, 0));
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 0 ), 3.14f, 0.0f, 90.0f));

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    Vertex v1(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.583f,  0.771f,  0.014f));
    Vertex v2(glm::vec3(1.0f,-1.0f, -1.0f), glm::vec3(0.609f,  0.115f,  0.436f));
    Vertex v3(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v4(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v5(glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v6(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    std::vector<Vertex> vertices{v1, v2, v3, v4, v5, v6};

    Mesh mesh(vertices);

    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.005f; // 0.0 units / second

    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(engine.programID);

        // take care of camera movement
        engine.movement(currentTime, lastTime, speed);

        // updat the projection
        glm::mat4 mvp = engine.camera.construct_mvp();

        GLuint MatrixID = glGetUniformLocation(engine.programID, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // Draw the Mesh
        mesh.Draw();

        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
