#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include "Engine.h"
#include "scenegraph.h"
#include "Camera.hpp"
#include "Triangle.h"
#include "lightsource.h"
#include "gridline.h"
#include <string>
#include "FrameBuffer.h"
#include "BVH_Node.h"



void test_raytracing(){
    point3 p0 = {0, 0, 0};
    point3 p1 = {1, 0, 0};
    point3 p2 = {0, 1, 0};


    auto Triangle1 = std::make_shared<Triangle>(p0, p1, p2, color3{0.5, 0.5, 0.5});

    std::vector<std::shared_ptr<Object>> all_objects {Triangle1};

    auto worldRaytracer = std::make_shared<BVH_Node>(all_objects, 0, all_objects.size());

    /**
     * Set up camera
     */
    auto rayTracingCamera = std::make_shared<Camera>(800, 1800, point3{0, 0, 10});
  //  std::cerr<<"Camera is at : "<<glm::to_string(camera.getPosition())<<"\n";

    std::cerr<<"The world is at coord z: "<<worldRaytracer->get_boundingBox().get_ax(2).min<< " " << worldRaytracer->get_boundingBox().get_ax(2).max<<" \n";

    rayTracingCamera->render(worldRaytracer, "imageRender-test.ppm");

}



int main(int argc, char* argv[])
{

    test_raytracing();

    Engine engine = Engine(1800, 800, engineCamera(glm::vec3( 0, 0, 10), 3.14f, 0.0f, 90.0f), SOURCE_DIR + (std::string)"/shaders");

    // only a single face of the object loaded..,
    auto entity1 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/frog.obj");

    auto entity2 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cone.obj");
    entity2->translate(-5, -5, 5);
    // to get the object identifier we can just count hte total number of objects stored in the scene grap

    Lightarray lights;
    Lightsource lamp(glm::vec3(1.0f, 0.0f, -0.5f), glm::vec3(1.0f, 1.0f, 0.0f));
    lights.addSource(lamp);

//    grid big_grid;
//    big_grid.gen_big_grid(1000, 501);
//
//    grid axes;
//    axes.gen_axes(1000);

    entity1 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/Grey.png");

    std::cout << "Texture is loaded" << std::endl;
//    auto entity2 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/frog.obj");
//    auto entity3 = std::make_shared<Entity>(SOURCE_DIR + (std::string)"/objects/cube.obj");
//
    entity2 -> texture = new Texture(SOURCE_DIR + (std::string)"/Textures/Grey.png");
//
//    entity2 -> scale(0.5, 0.5, 0.5);
//    entity2 -> translate(-10, -10, 0);
//
//    entity3 -> scale(0.4, 0.4, 0.4);
//    entity3->translate(-10, -10, 0);

    Node* node1 = new Node(entity1);
    Node* node2 = new Node(entity2);
//    Node* node2 = new Node(entity2);
//    Node* node3 = new Node(entity3);

    node1 -> setParent(engine.engineWorld);
    node2 ->setParent(engine.engineWorld);
    engine.engineWorld -> setName("root");

    //setting the names so that they are displayed on the display on the left hand side
    node1 -> setName("frogsterfrogginson");
    node2 -> setName("aliensBuiltThePyramids");

    engine.engineWorld ->addKeyframe(0);

    entity1 -> scale(0.1, 0.1, 0.1);
    entity1 -> rotate(1, 2, 3, 4);

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


//    auto world = new Triangle(v1.Coordinates, v2.Coordinates, v3.Coordinates);
//    engine.world = world;

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.01f;

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

        engine.camera.movement(currentTime, lastTime, speed, engine.window);

        engine.update(shader);
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
