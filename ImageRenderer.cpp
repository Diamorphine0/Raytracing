//
// Created by tudor on 10/12/23.
//

#include "ImageRenderer.h"
#include "GLFW/glfw3.h"

#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

ImageRenderer::ImageRenderer(int height, int width){
    image_height = height;
    image_width = width;

    pixel_colors = std::vector< std::vector< Color >> (image_height,
                                                       std::vector< Color >(image_width, Color(0, 0, 0)));

}


void ImageRenderer::reset_pixels() {
    pixel_colors = std::vector< std::vector< Color >> (image_height,
                                                       std::vector< Color >(image_width, Color(0, 0, 0)));
}

bool ImageRenderer::set_pixel(int pixel_row, int pixel_column, const Color &color) {
    if(pixel_row < 0 || pixel_row >= image_height)
        return false;
    if(pixel_column < 0 || pixel_column >= image_width)
        return false;
    pixel_colors[pixel_row][pixel_column] = color;
    return true;
}

bool ImageRenderer::set_all_pixels(const std::vector<std::vector<Color>> &colors) {
    if(colors.size() != image_height)
        return false;
    for (const auto & colors_row : colors){
        if (colors_row.size() != image_width)
            return false;
    }
    pixel_colors = colors;
    return true;
}

void ImageRenderer::render_image() {

    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    // Set OpenGL version to 3.3 and use the core profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(image_width, image_height, "Rendered Image", NULL, NULL);
    if (!window) {
        fprintf(stderr, "Failed to open GLFW window\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Set the viewport size
    glViewport(0, 0, image_width, image_height);

    while (!glfwWindowShouldClose(window)) {

        // Loop through each pixel and set its color
        // This is not the way to go, we should instead create a texture object first from our pixel_colors vector, and then display this texture object on the window

        //replace from...

        // Clear the framebuffer
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < image_height; ++i) {
            for (int j = 0; j < image_width; ++j) {
                glBegin(GL_POINTS);

                // Set the color of the pixel
                glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

                // Draw the pixel at normalized coordinates
                glVertex2f(-1.0f + 2.0f * j / image_width, -1.0f + 2.0f * i / image_height);

                glEnd();
            }
        }

        // Swap buffers and poll events
        glfwSwapBuffers(window);
        glfwPollEvents();

        //replace until...

        // Check for window close events
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(window))
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}


