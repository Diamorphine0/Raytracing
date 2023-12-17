#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "engineCamera.h"
#include "Camera.hpp"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

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
        programID = LoadShaders( "/Users/david/Desktop/polytechnique/01. semester 3/CSE201/project/Raytracing/vertexshader.shader", "/Users/david/Desktop/polytechnique/01. semester 3/CSE201/project/Raytracing/fragmentshader.shader" );

        // Ensure we can capture the escape key being pressed below
        glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
        // Cull triangles which normal is not towards the camera
        glEnable(GL_CULL_FACE);
    }

    void movement(float& currentTime, float& lastTime, float& speed){

        lastTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);

        // Move forward
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
            camera.position += camera.direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
            camera.position -= camera.direction * deltaTime * speed;
        }

        // Strafe right
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
            camera.position += camera.right * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
            camera.position -= camera.right * deltaTime * speed;
        }
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

            if(ImGui::Button("Raytrace Option")){
                // sets some bool to true, which affects the execution of our raytracing loop
            };

            // raytrace_parameter also affects the execution of our raytracing loop
            float raytrace_parameter = 0;
            ImGui::SliderFloat("Raytrace Slider", &raytrace_parameter, -10, 10);

            if(ImGui::Button("Raytrace")){
                counter++;
                rayTracingCamera = new Camera(height, width, camera.position);
                rayTracingCamera->render(*world);

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

    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    Camera *rayTracingCamera;
    Hittable *world;
};

#endif // ENGINE_H
