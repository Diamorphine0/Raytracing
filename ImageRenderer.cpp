//
// Created by tudor on 10/12/23.
//

#include "ImageRenderer.h"

ImageRenderer::ImageRenderer(int height, int width){
    image_height = height;
    image_width = width;

    pixel_colors = std::vector< std::vector< color3 >> (image_height,
                                                       std::vector< color3 >(image_width, color3(0, 0, 0)));

}

void ImageRenderer::reset_pixels() {
    pixel_colors = std::vector< std::vector< color3 >> (image_height,
                                                       std::vector< color3 >(image_width, color3 (0, 0, 0)));
}

bool ImageRenderer::set_pixel(int pixel_row, int pixel_column, const color3 &color) {
    if(pixel_row < 0 || pixel_row >= image_height)
        return false;
    if(pixel_column < 0 || pixel_column >= image_width)
        return false;
    pixel_colors[pixel_row][pixel_column] = color;
    return true;
}

void ImageRenderer::Raytrace(){

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

    // Get the primary monitor
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();

    // Get the video mode of the primary monitor
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    int monitorX, monitorY, monitorWidth, monitorHeight;
    glfwGetMonitorWorkarea(monitor, &monitorX, &monitorY, &monitorWidth, &monitorHeight);

    auto window = glfwCreateWindow( image_width, image_height, "Engine Project", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    auto fb = new frameBuffer(image_width, image_height);
    fb -> BindData(&pixel_colors);

    Shader* shader = new Shader(SOURCE_DIR + '/shaders/rayVertex.shader', SOURCE_DIR + '/shaders/rayFragment.shader');

    do{
        shader -> Bind();
        fb -> Bind();
        glfwSwapBuffers(window);
    }
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

}

bool ImageRenderer::set_all_pixels(const std::vector<std::vector<color3>> &colors) {
    if(colors.size() != image_height)
        return false;
    for (const auto & colors_row : colors){
        if (colors_row.size() != image_width)
            return false;
    }
    pixel_colors = colors;
    return true;
}

void ImageRenderer::render_image(const std::string &file_image) {
    std::ofstream  outFile(file_image);

    if(outFile.is_open()){
        std::cerr<<"Ok?\n";
    }
    outFile<<"P3\n";
    outFile<<image_width<<" "<<image_height<<" "<<255<<"\n";
    for(int i = 0; i < image_height; i++){
        for(int j = 0; j < image_width; j++){
            outFile<<static_cast<int> (pixel_colors[i][j].x * 255.999)<<" "<<static_cast<int> (pixel_colors[i][j].y * 255.999)<<" "<<static_cast<int> (pixel_colors[i][j].z * 255.999)<<"\n";

        }
    }
    std::cerr<<"Done printing!\n"<<image_height<<" "<<image_width<<"\n";
    outFile.flush();
}

