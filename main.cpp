#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"

#include <engineCamera.h>
#include <ecs.h>

class Engine{
public:
    Engine(float width, float height, engineCamera camera): camera(camera){

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
        programID = LoadShaders( "../vertexshader.shader", "../fragmentshader.shader" );

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

            if(ImGui::Button("Raytrace"))
                counter++;

            ImGui::ColorEdit3("Set Object Color", (float*) &clear_color);
            // we should now be able to change the color of the vertex.

            ImGui::Text("Raytracings done = %d", counter);
            //   ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
        };

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    GLFWwindow* window;
    GLuint programID;
    engineCamera camera;
};

int main()
{

    Engine engine = Engine(1024, 768, engineCamera(glm::vec3( 0, 0, 5 ), 3.14f, 0.0f, 90.0f));

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    Vertex v1(glm::vec3(-1.0f,-1.0f,-1.0f), glm::vec3(0.583f,  0.771f,  0.014f));
    Vertex v2(glm::vec3(-1.0f,-1.0f, 1.0f), glm::vec3(0.609f,  0.115f,  0.436f));
    Vertex v3(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v4(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v5(glm::vec3(1.0f, 2.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    Vertex v6(glm::vec3(1.0f, 0.0f, 1.0f), glm::vec3(0.327f,  0.483f,  0.844f));
    std::vector<Vertex> vertices{v1, v2, v3, v4, v5, v6};

    Mesh mesh(vertices);

    float currentTime = glfwGetTime();
    float lastTime;

    float speed = 0.005f; // 0.0 units / second

    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(engine.programID);

        // take care of camera movement
        engine.movement(currentTime, lastTime, speed);

        // updat the projection
        glm::mat4 mvp = engine.camera.construct_mvp();

        GLuint MatrixID = glGetUniformLocation(engine.programID, "MVP");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

        // Draw the Mesh
        mesh.Draw();

        engine.update();
    }
    while( glfwGetKey(engine.window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(engine.window) == 0 );

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
