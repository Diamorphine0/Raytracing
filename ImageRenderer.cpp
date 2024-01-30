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

// Function to set up vertex buffer for points
void SetupPointBuffer(GLuint& VAO, GLuint& VBO)
{
    GLfloat pointVertices[] = { 0.0f, 0.0f };  // A single point at the origin

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pointVertices), pointVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

// Function to render points based on the data buffer
void RenderPoints(const std::vector<std::vector<glm::vec3>>& colorData, GLuint& VAO, GLuint& VBO, Shader* shader)
{

    glBindVertexArray(VAO);

    // Iterate through the data buffer and render a point for each pixel
    for (size_t y = 0; y < colorData.size(); ++y)
    {
        for (size_t x = 0; x < colorData[y].size(); ++x)
        {
            GLfloat xPos = static_cast<GLfloat>(x) / static_cast<GLfloat>(colorData[y].size()) * 2.0 - 1.0;
            GLfloat yPos = 1.0 - static_cast<GLfloat>(y) / static_cast<GLfloat>(colorData.size()) * 2.0;

            glm::vec3 pixelColor = colorData[y][x];
            glUniform3f(glGetUniformLocation(shader ->getID(), "pointColor"), pixelColor.x, pixelColor.y, pixelColor.z);

            glUniform2f(glGetUniformLocation(shader ->getID(), "position"), xPos, yPos);

            glDrawArrays(GL_POINTS, 0, 1);
        }
    }

    // Reset state
    glBindVertexArray(0);
    glUseProgram(0);
}

int ImageRenderer::Raytrace(){

    // Initialise GLFW
    glewExperimental = true; // Needed for core profile
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( image_width, image_height, "Raytracing output", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW
    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);


    Shader* shader = new Shader(SOURCE_DIR+(std::string)"/shaders/rayVertex.shader", SOURCE_DIR+(std::string)"/shaders/rayFragment.shader");

    GLuint VAO;
    GLuint VBO;
    shader -> Bind();
    SetupPointBuffer(VAO, VBO);

    do{
        glClear( GL_COLOR_BUFFER_BIT );

        shader -> Bind();

        RenderPoints(pixel_colors, VAO, VBO, shader);

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    return -1;
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

