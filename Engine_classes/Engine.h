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
class TextData {
public:
    char buffer[256] = {};

    const char* getText() const {
        return buffer;
    }
};

class Engine{
public:

    Engine(engineCamera camera, const std::string &shader_path);

    void update(Shader* shader);

    // ImGUI rendering functions
    void LoadEngine();
    void RenderProperties();
    void RenderHierarchy();
    void RenderStats();
    void RenderAnimation();
    void RenderAddObject();
    void displayUpdate();

    inline float convertFrameToTime(int frame){return frame/framesPerSecond;};

    // Scene Graph Root Node - we can achieve camera movement by applying entity transformations to the object.
    Node* engineWorld;

    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    frameBuffer* fb;
    Shader* shader;
    Shader* shaderLine;
    Shader* shaderAx;

    int currentFrame = 0;
    int framesPerSecond = 30;

    bool animate = false;

    grid big_grid;
    grid axes;

    //this is data useful for the UI.
    TextData objectName;
    TextData objectTexture;
    TextData objectTag;

    //clicled object
    //Node* clicked;
private:
    std::vector<int> markedPositions;
};


#endif // ENGINE_H
