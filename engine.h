#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.hpp"
#include "engineCamera.h"
#include "scenegraph.h"
#include "Entity.h"
#include "frameBuffer.h"
#include <vector>
#include <string>
#include <iostream>
#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <fstream>
    #include <sstream>
#elif __APPLE__
    #include <sys/sysctl.h>
    #include <unistd.h>
    #include <mach/mach.h>
#else
#endif

#include "shader.h"
#include <thread>
#include <chrono>
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


// We need to figure out what goes into the engine class and what goes into the ECS class as well as how they relate to one another.


class Engine{
public:

    Engine(float width, float height, engineCamera camera);

    void update();

    // ImGUI rendering functions
    void LoadEngine();
    void RenderProperties();
    void RenderHierarchy();
    void RenderStats();
    void RenderAnimation();

    // Scene Graph Root Node - we can achieve camera movement by applying entity transformations to the object.
    Node* engineWorld;

    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    Camera *rayTracingCamera;
    Hittable *world;
    frameBuffer* fb;
    Shader* shader;
    ImFont* standardfont;
private:
    std::vector<int> markedPositions;
};


#endif // ENGINE_H
