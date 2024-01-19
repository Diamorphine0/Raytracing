// Here we will implement the ECS class.
#include "Engine.h"
#include <memory>
Engine::Engine(float width, float height, engineCamera camera, const std::string &shader_path): width(width), height(height), camera(camera){

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

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    // shader = new Shader("../Raytracing/vertexshader.shader", "../Raytracing/fragmentshader.shader");

    // It suffices to load the framebuffer here.
    fb = new frameBuffer(width, height);

    Entity* cameraentity = new Entity();
    engineWorld = new Node(cameraentity);

    shaderLine = new Shader(shader_path + "/vertexshaderLine.shader", shader_path + "/fragmentshaderLine.shader");
    shaderAx = new Shader(shader_path + "/vertexshaderAx.shader", shader_path + "/fragmentshaderAx.shader");

    big_grid.gen_big_grid(1000, 501);
    axes.gen_axes(1000);
}

void Engine::update(Shader* shader){

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::SetNextWindowSize(ImVec2(400,400));
    ImGui::SetNextWindowPos(ImVec2 (0,0));
    ImGui::Begin("Hierarchy");

    RenderHierarchy();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(800, 600));
    ImGui::SetNextWindowPos(ImVec2 (400, 0));
    ImGui::Begin("Engine Visualization");
    LoadEngine();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(400,200));
    ImGui::SetNextWindowPos(ImVec2 (0,400));
    ImGui::Begin("Properties");
    RenderProperties();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(300,600));
    ImGui::SetNextWindowPos(ImVec2 (1200,0));
    ImGui::Begin("Settings");
    RenderStats();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(1500,200));
    ImGui::SetNextWindowPos(ImVec2 (0,600));
    ImGui::Begin("Animation");
    RenderAnimation();
    ImGui::End();

    // Rendering
    ImGui::Render();

    fb -> Bind();

    camera.animateScene(engineWorld, *shader, animationTime, 0.01);

    big_grid.draw(*shaderLine, camera);
    axes.draw(*shaderAx, camera);

    fb -> Unbind();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void Engine::LoadEngine(){
    // we access the ImGui window size
    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

    // we rescale the framebuffer to the actual window size here and reset the glViewport
    fb -> Rescale(window_width, window_height);
    glViewport(0, 0, window_width, window_height);

    // we get the screen position of the window
    ImVec2 pos = ImGui::GetCursorScreenPos();

    // and here we can add our created texture as image to ImGui
    // unfortunately we need to use the cast to void* or I didn't find another way tbh
    ImGui::GetWindowDrawList()->AddImage(
        (void *) fb -> texture_id,
        ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height),
        ImVec2(0, 1),
        ImVec2(1, 0)
    );
}

void Engine::RenderProperties(){
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
    ImGui::SliderFloat("Rotate", &rotation, 0.0f, 360.0f);

    //Color selection
    ImVec4 color;
    ImGui::ColorEdit4("Color", &color.x);
};

void Engine::RenderStats(){
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Framerate:");
    ImGui::Text("Application average %.1f FPS", io.Framerate);

    static int counter = 0;
    ImGui::NewLine();
    ImGui::Text("Raytracings done = %d", counter);

    if(ImGui::Button("Raytrace")){
        counter++;
        rayTracingCamera = new Camera(height, width, camera.getPosition());
       // rayTracingCamera->render(world, "imageRender.ppm");
    }
}
struct EntityNode {
    int id;
    std::string name;
    std::vector<EntityNode> children;
};

void RenderEntityHierarchy(EntityNode& entity) {
    // Display each entity as a tree node
    if (ImGui::TreeNodeEx(entity.name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick)) {

        // Add drag-and-drop source
        if (ImGui::BeginDragDropSource()) {
            // Set payload to the entity's id
            ImGui::SetDragDropPayload("ENTITY_ID", &entity.id, sizeof(entity.id));
            ImGui::Text("Dragging %s", entity.name.c_str());
            ImGui::EndDragDropSource();
        }

        // Context menu when right-clicking an entity
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity")) {
            }
            if (ImGui::MenuItem("Create Child")) {
            }
            ImGui::EndPopup();
        }
        if (ImGui::BeginDragDropTarget()) {
            // Accept the payload
            const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ENTITY_ID");
            if (payload) {
                // Process the payload (in this example, rearrange the hierarchy)
                int draggedEntityId = *static_cast<const int*>(payload->Data);
                std::cout << "Dropped entity with ID " << draggedEntityId << " onto " << entity.name << std::endl;
                // Implement logic to rearrange the hierarchy based on the dropped entity ID
            }

            // End the drag-and-drop target
            ImGui::EndDragDropTarget();
        }

        // Render child entities recursively
        for (auto& child : entity.children) {
            RenderEntityHierarchy(child);
        }

        // End the tree node
        ImGui::TreePop();


    }
}

void Engine::RenderHierarchy() {
    ImGui::Text("Entity Hierarchy View");

    // Sample hierarchy with parent-child relationships
    static EntityNode rootNode = {1, "Root", {{2, "Child1"}, {3, "Child2", {{4, "Grandchild1"}, {5, "Grandchild2"}}}}};

    // Render the hierarchy
    RenderEntityHierarchy(rootNode);
}

void Engine::RenderAnimation() {
    ImGui::Begin("Animation");

    static int coarseFrame = 0;
    ImGui::SliderInt("Coarse Slider", &coarseFrame, 0, 500, "Frame %d");


    if (ImGui::Button("Mark Position")) {
        markedPositions.push_back(coarseFrame);
    }

    if (ImGui::Button("Clear All Marks")) {
        markedPositions.clear();
    }

    ImGui::Text("Coarse Frame: %d", coarseFrame);

    ImVec2 sliderMin = ImGui::GetItemRectMin();
    ImVec2 sliderMax = ImGui::GetItemRectMax();
    float sliderRange = sliderMax.x - sliderMin.x;

    for (int markedPosition : markedPositions) {
        float relativePosition = static_cast<float>(markedPosition - 0) / 500.0f;
        ImVec2 markPos = ImVec2(sliderMin.x + relativePosition * sliderRange, sliderMin.y -10);
        ImGui::GetWindowDrawList()->AddLine(ImVec2((markPos.x-5.5)*8, markPos.y - 80), ImVec2((markPos.x-5.5) *8, markPos.y - 40), IM_COL32(255, 0, 0, 255), 2.0f);
    }

    ImGui::End();
}