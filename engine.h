#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "engineCamera.h"
#include "Camera.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


// We need to figure out what goes into the engine class and what goes into the ECS class as well as how they relate to one another.
class Engine{
public:

    Engine(float width, float height, engineCamera camera): width(width), height(height), camera(camera){

        glewExperimental = true;

        if( !glfwInit() )
        {
            fprintf( stderr, "Failed to initialize GLFW\n" );
        }

        glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow( width, height, "Engine Project", NULL, NULL);

        if( window == NULL ){
            fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
            glfwTerminate();
        }

        glfwMakeContextCurrent(window);
        glewExperimental=true;
        if (glewInit() != GLEW_OK) {
            fprintf(stderr, "Failed to initialize GLEW\n");
        }

        // Enable depth test
        glEnable(GL_DEPTH_TEST);
        // Accept fragment if it closer to the camera than the former one
        glDepthFunc(GL_LESS);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
        ImGui_ImplOpenGL3_Init();

        // Change the shader path names
        programID = LoadShaders( "../Raytracing/vertexshader.shader", "../Raytracing/fragmentshader.shader" );

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        // Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);
    }

    void update(){

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        {
            static int counter = 0;
            ImGui::Text("Engine");

            // General Event Handling Functionality

            // Object picking will happen here as well

            if(ImGui::Button("Raytrace")){
                counter++;
                rayTracingCamera = new Camera(height, width, camera.position);
                rayTracingCamera->render(*world, "imageRender.ppm");
            }

            float obj_rot_angle = 0;
            ImGui::SliderFloat("Rotation agnle along (0,0,1)", &obj_rot_angle, -3.14, 3.14);


            ImGui::ColorEdit3("Set Object Color", (float*) &clear_color);
            // we should now be able to change the color of the vertex.

            ImGui::Text("Raytracings done = %d", counter);
            ImGuiIO& io = ImGui::GetIO();
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        };

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // We should add functionality to animate
    void animateScene(){

    }

    // scene graph -> which will store the relationship between the objects ->

    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    Camera *rayTracingCamera;
    Hittable *world;
};

#endif // ENGINE_H
