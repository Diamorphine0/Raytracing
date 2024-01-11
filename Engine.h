#pragma once
#ifndef ENGINE_H
#define ENGINE_H

#include "framebuffer.h"

// We need to figure out what goes into the engine class and what goes into the ECS class as well as how they relate to one another.
class Engine{
public:

    Engine(float width, float height, engineCamera camera);

    void update();

    void RenderProperties();
    void RenderHierarchy();
    void RenderStats();

    // Scene Graph - we can achieve camera movement by applying entity transformations to the object.
    Node* engineWorld;
    FrameBuffer* framebuffer;
    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
    int width, height;
    Camera *rayTracingCamera;
    Hittable *world;
};

#endif // ENGINE_H
