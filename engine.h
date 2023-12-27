#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.hpp"
#include "engineCamera.h"
#include "scenegraph.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


// We need to figure out what goes into the engine class and what goes into the ECS class as well as how they relate to one another.
class Engine{
public:

    Engine(float width, float height, engineCamera camera);

    void update(){

        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

        RenderUI();

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    void RenderUI(){

        static int counter = 0;
        ImGui::Text("Engine");

        if(ImGui::Button("Raytrace")){
            counter++;
            rayTracingCamera = new Camera(height, width, camera.getPosition());
            rayTracingCamera->render(world, "imageRender.ppm");
        }

        ImGui::Text("Transform Controls");

        // Translation sliders for X, Y, Z direction
        // we want to store the previous values
        static float translationX = 0.0f, translationY = 0.0f, translationZ = 0.0f;
        ImGui::SliderFloat("Translation X", &translationX, -10.0f, 10.0f);
        ImGui::SliderFloat("Translation Y", &translationY, -10.0f, 10.0f);
        ImGui::SliderFloat("Translation Z", &translationZ, -10.0f, 10.0f);

        // Scaling slider
        static float scale = 1.0f;
        ImGui::SliderFloat("Scale", &scale, 0.1f, 3.0f);

        // Rotation slider
        static float rotation = 0.0f;
        ImGui::SliderFloat("Rotation", &rotation, 0.0f, 360.0f);
        ImGui::Text("Raytracings done = %d", counter);
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    };

    // scene graph -> which will store the relationship between the objects ->

    // do we want to select the currently selected object.
    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    Camera *rayTracingCamera;
    Node* engineWorld;
    Hittable *world;
};

#endif // ENGINE_H
