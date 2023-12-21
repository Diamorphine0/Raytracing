#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "engine.h"
#include "ecs.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "objloader.hpp"

#include <filesystem>

int main()
{
    std::cerr<<"TEST1\n";


    std::cerr<<"TEST\n";

    auto rayTracingCamera = new Camera(1024, 768, Point3(0, 0, 0));
    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 0 ), 3.14f, 0.0f, 90.0f));

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);


    //Loading the vertices from the .obj file (For now there is a lot of information lost)
    //!Vertex class (in esc.h) was modified as there seems to be no color information in .obj
    ObjectLoader objectLoader;
    std::vector<glm::vec3> vertices_raw;
    objectLoader.load_object("../Raytracing/demo/demo2.obj", vertices_raw);

    std::vector<Vertex> vertices;
    for (std::vector<glm::vec3>::iterator it = vertices_raw.begin(); it != vertices_raw.end(); it++) {
        vertices.push_back(Vertex(*it));
    }

    //Making mesh from the uploaded vertices
    Mesh mesh(vertices);
    mesh.rotate_mesh(glm::vec3(0, 0, 1.0f), 3.14/2);

    auto world = new Triangle(vertices[0].Coordinates, vertices[1].Coordinates, vertices[-1].Coordinates); //!For now it's 3 random points, don't know what is the logic behind
    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    //CHANGING THE SPEED (Around 0.0001f works well to enjoy the perspective)
    float speed = 0.0001f; // 0.0 units / second

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
