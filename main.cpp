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
#include "DielectricMaterial.h"
#include "DiffuseMaterial.h"


void add_node(std::shared_ptr<Entity> &aux, Engine &engine, std::string name){
    auto aux_node = new Node(aux);
    aux_node ->setParent(engine.engineWorld);
    aux_node->setName(name);
    engine.selectedNode = aux_node;
}
void build_scene(Engine &engine, std::string path){
    auto brick_text = std::make_shared<Texture>(path + "/Textures/brick.png");
    auto purple_text = std::make_shared<Texture>(path + "/Textures/purple.png");

    auto glass = std::make_shared<DielectricMaterial>(10);
    auto diffuse = std::make_shared<DiffuseMaterial>(purple_text);



    auto sphere = std::make_shared<Entity>(path + "/objects/sphere.obj");
    sphere->texture = purple_text;
    sphere->translate(0, 1, 0);
    sphere->material = glass;

    auto cube = std::make_shared<Entity>(path + "/objects/cube.obj");
    cube->translate(0, 0, -10);
    cube->material = diffuse;
    cube ->texture = brick_text;


    auto plane = std::make_shared<Entity>(path + "/objects/cube.obj");
   // plane->scale(1000, 1000, 1000);
    plane->scale(10, 0.001, 10);
    plane->translate(-2, 0, 0);

    plane->texture = brick_text;
    plane->material = diffuse;


    auto aux_entity = std::make_shared<Entity> (path + "/objects/triangle.obj");
    aux_entity->scale(0.001, 0.001, 0.001);
    aux_entity->texture = purple_text;
    aux_entity->material = diffuse;

    add_node(plane, engine, "plane");
    add_node(cube, engine, "cube");
    add_node(sphere, engine, "sphere");

}

int main(int argc, char* argv[])
{

    Engine engine = Engine(engineCamera(glm::vec3( 0, 0.5, 10), 3.14f, 0.0f, 90.0f), SOURCE_DIR );

    Lightarray lights;
    Lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

    engine.engineWorld -> setName("Scene Graph Root (Engine Camera)");

    float currentTime = glfwGetTime();
    float lastTime = currentTime;

    float speed = 5.0f;

    Shader* shader = new Shader(SOURCE_DIR + (std::string)"/shaders/vertexshader.shader", SOURCE_DIR + (std::string) "/shaders/fragmentshader.shader");

    float animationTime = 0;

    build_scene(engine, SOURCE_DIR);
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

        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        engine.update(shader);
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
