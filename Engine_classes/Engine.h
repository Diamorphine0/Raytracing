#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.hpp"
#include "engineCamera.h"
#include "scenegraph.h"
#include "Entity.h"


#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "FrameBuffer.h"
#include "gridline.h"

// We need to figure out what goes into the engine class and what goes into the ECS class as well as how they relate to one another.


class Engine{
public:

    Engine(float width, float height, engineCamera camera, const std::string &shader_path);

    void update(Shader* shader);

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
    frameBuffer* fb;
    Shader* shader;
    Shader* shaderLine;
    Shader* shaderAx;

    grid big_grid;
    grid axes;
private:
    std::vector<int> markedPositions;
};


#endif // ENGINE_H
