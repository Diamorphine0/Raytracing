// Here we will implement the ECS class.
#include "Engine.h"
#include "Utilities.hpp"
#include "scenegraph.h"
#include <memory>
#include "TriangleMesh.h"
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
    ImGui::StyleColorsDark();                                 // Set theme to dark

    // we set new standard font
    io.Fonts->AddFontDefault();
    standardfont = io.Fonts->AddFontFromFileTTF("../Raytracing/fonts/NotoSans.ttf", 20.0f);
    IM_ASSERT(standardfont != NULL);

    // we set the desired ImGui style properties
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;

    style.ScrollbarRounding = 0;
    style.WindowRounding = 3.0f;

    colors[ImGuiCol_Button] = ImColor(169,169,169,100);
    colors[ImGuiCol_ButtonHovered] = ImColor(211,211,211,100);
    colors[ImGuiCol_ButtonActive] = ImColor(128,128,128,100);
    colors[ImGuiCol_SliderGrab] = ImColor(169,169,169,100);
    colors[ImGuiCol_SliderGrabActive] = ImColor(211,211,211,100);

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);


    // It suffices to load the framebuffer here.
    fb = new frameBuffer(width, height);

    engineWorld = new Node(std::make_shared<Entity>());

    shaderLine = new Shader(shader_path + "/vertexshaderLine.shader", shader_path + "/fragmentshaderLine.shader");
    shaderAx = new Shader(shader_path + "/vertexshaderAx.shader", shader_path + "/fragmentshaderAx.shader");

    big_grid.gen_big_grid(1000, 501);
    axes.gen_axes(1000);

    initialWindowSize = ImVec2(width, height);
}

// obtain the current (rescaled) size of the GLFW parent window
void GetWindowSize(GLFWwindow* window, int& width, int& height) {
    if (window != nullptr) {
        glfwGetWindowSize(window, &width, &height);
    }
    else {
        width = 0;
        height = 0;
    }
}
float lastCPUPercentage = 0.0f;
std::chrono::time_point<std::chrono::high_resolution_clock> lastUpdateTime;

float GetCPUUsageMacOS() {
#ifdef __APPLE__
    host_cpu_load_info_data_t cpuinfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics64(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info64_t)&cpuinfo, &count) == KERN_SUCCESS) {
        unsigned long long totalTicks = 0;
        for (int i = 0; i < CPU_STATE_MAX; ++i) {
            totalTicks += cpuinfo.cpu_ticks[i];
        }
        unsigned long long idleTicks = cpuinfo.cpu_ticks[CPU_STATE_IDLE];
        float cpuUsage = 100.0f * (1.0f - static_cast<float>(idleTicks) / totalTicks);

        return cpuUsage;
    }

    return -1.0f;
#else
    // Return default value for non-MacOS platforms
    return -1.0f;
#endif
}


void Engine::update(Shader* shader){

    // we store the GLFW window size
    int width, height;
    GetWindowSize(window, width, height);

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // we push the standard font
    ImGui::PushFont(standardfont);

    // we set the rounding radius and padding for all buttons
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(5, 5));

    // we rescale the ImGui windows and fix their positions
    // we render the GUI functionalities onto each window with a dedicated function

    ImGui::SetNextWindowSize(ImVec2(0.25*width,0.375*height));
    ImGui::SetNextWindowPos(ImVec2 (0,0));
    ImGui::Begin("Hierarchy");
    RenderHierarchy();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.5*width, 0.75*height));
    ImGui::SetNextWindowPos(ImVec2 (0.25*width, 0));
    ImGui::Begin("Engine Visualization");
    LoadEngine();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.25*width,0.375*height));
    ImGui::SetNextWindowPos(ImVec2 (0,0.375*height));
    ImGui::Begin("Properties");
    RenderProperties();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.25*width,0.75*height));
    ImGui::SetNextWindowPos(ImVec2 (0.75*width,0));
    ImGui::Begin("Settings");
    RenderStats();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(width,0.25*height));
    ImGui::SetNextWindowPos(ImVec2 (0,0.75*height));
    ImGui::Begin("Animation");
    RenderAnimation();
    ImGui::End();

    // we pop the standard font
    ImGui::PopFont();

    // we pop the custom button style
    ImGui::PopStyleVar(2);

    // Rendering
    ImGui::Render();

    fb -> Bind();

    camera.renderScene(engineWorld, *shader);

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
    //static float rotation = 0.0f;
    //ImGui::SliderFloat("Rotate", &rotation, 0.0f, 360.0f);

    if(ImGui::Button("Apply Transformations")){
        this->engineWorld->entity->translate(translationX, translationY, translationZ);
        this->engineWorld->entity->scale(scale, scale, scale);
        translationX = 0.0f;
        translationY = 0.0f;
        translationZ = 0.0f;
        scale = 1.0f;
    }

    //Color selection
    ImVec4 color;
    ImGui::ColorEdit4("Color", &color.x);
};

float minFrameRate = FLT_MAX;
float maxFrameRate = 0.0f;
bool isDarkMode = false;

void Engine::RenderStats(){

    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Average FPS: %.1f", 1000.0f / io.Framerate);
    float currentFrameRate = 1000.0f / io.Framerate;
    minFrameRate = std::min(minFrameRate, currentFrameRate);
    maxFrameRate = std::max(maxFrameRate, currentFrameRate);

    static bool showStats = true;
    ImGui::Checkbox("Additional Statistics", &showStats);

    if (showStats) {
        ImGui::Separator();
        ImGui::Text("Fetching Additional Statistics:");


        ImGui::Text("Min FPS: %.1f", minFrameRate);
        ImGui::Text("Max FPS: %.1f", maxFrameRate);
        //placeholder to be connected with actual number of entities
        int NumEntities = 1;
        float lastCPUPercentage = GetCPUUsageMacOS();
        ImGui::Text("Number of Entities: %d", 1);
        if (lastCPUPercentage >= 0.0f) {
            lastUpdateTime = std::chrono::high_resolution_clock::now();
            ImGui::Text("CPU Usage: %.3f%%", lastCPUPercentage);
        } else {
            ImGui::Text("CPU Usage: N/A (Not supported on this platform)");
        }

        ImGui::Separator();
    }


    if (ImGui::Button("Set Dark/Light Mode", ImVec2(180, 30))) {
        isDarkMode = !isDarkMode;

        // Adjust ImGui style based on the mode
        if (isDarkMode) {
            ImGui::StyleColorsDark();
        } else {
            ImGui::StyleColorsLight();
        }
    }



    static int counter = 0;
    ImGui::NewLine();
    ImGui::Text("Raytracings done = %d", counter);
    ImGui::NewLine();
    ImGui::Text("Frame to Raytrace: %d ", currentFrame);
    if(ImGui::Button("Raytrace")){
        //generate world at time t
        //i go through the scene graph and compute the right matrices for entities at time t
        std::vector<std::shared_ptr<Entity>> all_entities;
        engineWorld->dfs_entitity_setup(currentFrame, all_entities);

        std::vector<std::shared_ptr<Object>> all_objects;
        all_objects.reserve(all_entities.size());
        for(const auto &e:all_entities){
            all_objects.emplace_back(std::make_shared<TriangleMesh>(e));
        }

        auto worldRaytracer = std::make_shared<BVH_Node>(all_objects, 0, all_objects.size());
        counter++;
        /**
         * Set up camera
         */
        auto rayTracingCamera = std::make_shared<Camera>(height, width, camera.getPosition());
        std::cerr<<"Camera is at : "<<glm::to_string(camera.getPosition())<<"\n";

        std::cerr<<"The world is at coord z: "<<worldRaytracer->get_boundingBox().get_ax(2).min<< " " << worldRaytracer->get_boundingBox().get_ax(2).max<<" \n";

        rayTracingCamera->render(worldRaytracer, "imageRender-frame.ppm");

        // rayTracingCamera = new Camera(height, width, camera.getPosition());
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

    // we should have buttons to stop and play the animation

    //static int coarseFrame = 0;
    ImGui::SliderInt("Coarse Slider", &currentFrame, 0, 2000, "Frame %d");

    // we want to have an animate condition
    if(ImGui::Button("Play")){
        animate = true;
    }

    ImGui::SameLine();

    if(ImGui::Button("Pause")){
        animate = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Mark Position")) {
        // Add the keyframe
        engineWorld ->addKeyframe(currentFrame);

        markedPositions.push_back(currentFrame);
    }

    ImGui::SameLine();

    if (ImGui::Button("Clear All Marks")) {
        markedPositions.clear();
    }

    ImGui::Text("Coarse Frame: %d", currentFrame);

    ImVec2 sliderMin = ImGui::GetItemRectMin();
    ImVec2 sliderMax = ImGui::GetItemRectMax();
    float sliderRange = sliderMax.x - sliderMin.x;

    // Get the size of the ImGui window
    ImVec2 windowSize = ImGui::GetWindowSize();

    float scaleFactor = windowSize.x / initialWindowSize.x;

    for (int markedPosition : markedPositions) {
        // Calculate the relative position based on the current window size
        float relativePosition = static_cast<float>(markedPosition) / 720.0f;
        ImVec2 markPos = ImVec2(sliderMin.x + relativePosition * sliderRange, sliderMin.y - 10);

        // Scale the position based on the window size
        markPos.x *= scaleFactor;

        //Draw the red line
        ImGui::GetWindowDrawList()->AddLine(
            ImVec2((markPos.x) * 3, markPos.y - 60),
            ImVec2((markPos.x) * 3, markPos.y - 30),
            IM_COL32(255, 0, 0, 255),
            2.0f
            );
    }
    ImGui::End();
}

void Engine::RenderAddObject(){
    ImGui::Text("Here, you can add an object. Make sure \nthat the corresponding .obj file exists \nin the objects folder and input its name \nbelow!");
    ImGui::InputText("##objectName", objectName.buffer, sizeof(objectName.buffer));
    ImGui::Text("Here, add the texture you want to assign \nto the object! If no texture is provided, \nthe program will automatically assign \na default texture.");
    ImGui::InputText("##objectTexture", objectTexture.buffer, sizeof(objectTexture.buffer));

    if (ImGui::Button("Initialise object")){
        std::string nameString;
        for (int i = 0; i < 256 && objectName.buffer[i] != '\0'; ++i) {
            if (!std::isspace(static_cast<unsigned char>(objectName.buffer[i]))) {
                nameString += objectName.buffer[i];
            }
        }

        std::string textureString;
        for (int i = 0; i < 256 && objectTexture.buffer[i] != '\0'; ++i) {
            if (!std::isspace(static_cast<unsigned char>(objectTexture.buffer[i]))) {
                textureString += objectTexture.buffer[i];
            }
        }

        std::cout << SOURCE_DIR << std::endl;
        nameString = SOURCE_DIR + (std::string)"/objects/" + (std::string)nameString;
        textureString = SOURCE_DIR + (std::string)"/Textures/" + (std::string)textureString;

        try {
            auto entity = std::make_shared<Entity>(nameString.c_str());
            entity -> texture = new Texture(textureString.c_str());

            Node* node = new Node(entity);

            node -> setParent(this -> engineWorld);
        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        for(int i=0; i < 256; i++){
            objectName.buffer[i] = '\0';
            objectTexture.buffer[i] = '\0';
        }
    }
}
