#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "lightsource.h"
#include "gridline.h"
#include "framebuffer.h"

int main()
{

    auto rayTracingCamera = new Camera(1800, 800, Point3(0, 0, 0));
    Engine engine = Engine(1800, 800, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f));

    // only a single face of the object loaded..,
    Entity* entity1 = new Entity("../Raytracing/objects/cube.obj");

    // to get the object identifier we can just count hte total number of objects stored in the scene grap

    Lightarray lights;
    Lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

    grid big_grid;
    big_grid.gen_big_grid(1000, 501);

    grid axes;
    axes.gen_axes(1000);

    entity1 -> texture = new Texture("../Raytracing/Textures/Grey.png");

    Node* node1 = new Node(entity1);

    node1 -> setParent(engine.engineWorld);

    engine.engineWorld->addKeyframe(0);

    entity1 -> scale(0.1, 0.1, 0.1);
    entity1 -> rotate(1, 1, 1, 1);
    entity1 -> translate(10, 10, 10);

    engine.engineWorld->addKeyframe(10);


//    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
//    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.05f;

    Shader* shader = new Shader("../Raytracing/vertexshader.shader", "../Raytracing/fragmentshader.shader");

    float animationTime = 0;

    do{
       shader -> Bind();

        //this should handle lighting loading
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

        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        // the render scene and animate scene functionalities should be disjoint.
        engine.camera.animateScene(engine.engineWorld, *shader, animationTime, 0.01);
        shader -> Unbind();

        engine.update(shader);
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
