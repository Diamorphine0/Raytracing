// Here we will implement the ECS class.
#include "Engine.h"
#include "Utilities.hpp"
#include "scenegraph.h"
#include <memory>
#include "TriangleMesh.h"
#include "Dielectric_Material.h"
#include "Diffuse_Material.h"

Engine::Engine(engineCamera camera, const std::string &root_path): width(width), height(height), camera(camera){

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

    this->width = monitorWidth;
    this->height = monitorHeight;
    window = glfwCreateWindow( this->width, this->height, "Engine Project", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

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

    // we set new standard font
    io.Fonts->AddFontDefault();
    standardfont = io.Fonts->AddFontFromFileTTF((root_path + (std::string)"/fonts/NotoSans.ttf").c_str(), 20.0f);
    IM_ASSERT(standardfont != NULL);

    // we set the desired ImGui style properties
    ImGuiStyle& style = ImGui::GetStyle();
    auto& colors = style.Colors;

    style.ScrollbarRounding = 0;
    style.WindowRounding = 3.0f;

    // change color of title bars
    style.Colors[ImGuiCol_TitleBg] = ImColor(35,35,35,35);
    style.Colors[ImGuiCol_TitleBgActive] = ImColor(35,35,35,35);
    style.Colors[ImGuiCol_TitleBgCollapsed] = ImColor(35,35,35,35);

    // change color of buttons and sliders
    colors[ImGuiCol_Button] = ImColor(169,169,169,100);
    colors[ImGuiCol_ButtonHovered] = ImColor(211,211,211,100);
    colors[ImGuiCol_ButtonActive] = ImColor(211,211,211,100);

    colors[ImGuiCol_SliderGrab] = ImColor(169,169,169,100);
    colors[ImGuiCol_SliderGrabActive] = ImColor(169,169,169,100);
    style.Colors[ImGuiCol_FrameBg] = ImColor(120,120,120,100);
    style.Colors[ImGuiCol_FrameBgHovered] = ImColor(120,120,120,100);
    style.Colors[ImGuiCol_FrameBgActive] = ImColor(120,120,120,100);

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

    shaderLine = new Shader(root_path + (std::string)"/shaders" + "/vertexshaderLine.shader", root_path + (std::string)"/shaders" + "/fragmentshaderLine.shader");
    shaderAx = new Shader(root_path + (std::string)"/shaders" + "/vertexshaderAx.shader", root_path + (std::string)"/shaders" + "/fragmentshaderAx.shader");

    big_grid.gen_big_grid(1000, 501);
    axes.gen_axes(1000);
}

// stores the current (rescaled) size of the GLFW parent window in two parameters passed by reference
void GetWindowSize(GLFWwindow* window, int& width, int& height) {
    if (window != nullptr) {
        glfwGetWindowSize(window, &width, &height);
    }
    else {
        width = 0;
        height = 0;
    }
}

void Engine::update(Shader* shader){

    glfwPollEvents();

    displayUpdate();

    fb -> Bind();

    camera.Clear();
    if(animate){
        big_grid.draw(*shaderLine, camera);
        camera.animateScene(engineWorld, *shader, currentFrame);
    }
    else{
        big_grid.draw(*shaderLine, camera);
        axes.draw(*shaderAx, camera);
        camera.renderScene(engineWorld, *shader, currentFrame);
    }

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

void Engine::displayUpdate(){

    // we store the GLFW window size
    int width, height;
    GetWindowSize(window, width, height);

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

    ImGui::SetNextWindowSize(ImVec2(0.2*width,0.375*height));
    ImGui::SetNextWindowPos(ImVec2 (0,0));
    ImGui::Begin("Hierarchy");
    RenderHierarchy();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.6*width, 0.75*height));
    ImGui::SetNextWindowPos(ImVec2 (0.2*width, 0));
    ImGui::Begin("Engine Visualization");
    LoadEngine();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.2*width,0.375*height));
    ImGui::SetNextWindowPos(ImVec2 (0,0.375*height));
    ImGui::Begin("Properties");
    RenderProperties();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.2*width,0.3*height));
    ImGui::SetNextWindowPos(ImVec2 (0.8*width,0));
    ImGui::Begin("Settings");
    RenderStats();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2(0.2*width,0.45*height));
    ImGui::SetNextWindowPos(ImVec2 (0.8*width,0.3*height));
    ImGui::Begin("Add Object");
    RenderAddObject();
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
}

void Engine::RenderProperties(){
    // Translation sliders for X, Y, Z direction
    // we want to store the previous values
    static float translationX = 0.0f, translationY = 0.0f, translationZ = 0.0f;
    ImGui::SliderFloat("Translation X", &translationX, -10.0f, 10.0f);
    ImGui::SliderFloat("Translation Y", &translationY, -10.0f, 10.0f);
    ImGui::SliderFloat("Translation Z", &translationZ, -10.0f, 10.0f);

    static float rotationX = 0.0f, rotationY = 0.0f, rotationZ = 0.0f;
    ImGui::SliderFloat("Rotation X", &rotationX, 0.f, 10.0f);
    ImGui::SliderFloat("Rotation Y", &rotationY, 0.f, 10.0f);
    ImGui::SliderFloat("Rotation Z", &rotationZ, 0.f, 10.0f);

    // Scaling slider
    static float scale = 1.0f;
    ImGui::SliderFloat("Scale", &scale, 0.1f, 3.0f);

    // Rotation slider
    //static float rotation = 0.0f;
    //ImGui::SliderFloat("Rotate", &rotation, 0.0f, 360.0f);

    if(ImGui::Button("Apply transformations")){
        this->selectedNode->entity->translate(translationX, translationY, translationZ);
        this->selectedNode->entity->rotate(rotationX, 1, 0, 0);
        this->selectedNode->entity->rotate(rotationY, 0, 1, 0);
        this->selectedNode->entity->rotate(rotationZ, 0, 0, 1);
        this->selectedNode->entity->scale(scale, scale, scale);
        translationX = 0.0f;
        translationY = 0.0f;
        translationZ = 0.0f;
        rotationX = 0.0f;
        rotationY = 0.0f;
        rotationZ = 0.0f;
        scale = 1.0f;
        // we want to set the color of the object as well - this may be a bit harder
    }

    //
    static ImVec4 color;
    ImGui::ColorEdit3("Color", &color.x);
    if(ImGui::Button("Apply new ambient colour")){
        this->selectedNode->entity->setAmbience(color.x, color.y, color.z);
        color = {0,0,0,0};
    }
    if(ImGui::Button("Remove ambience")){
        this->selectedNode->entity->setAmbience(1.0f, 1.0f, 1.0f);
    }
};

void Engine::RenderEntityHierarchy(Node& node) {
    bool isClicked = ImGui::TreeNodeEx(node.name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);

    if(isClicked){
        selectedNode = &node;

        std::vector<Node*> children = node.getChildren();
        for (auto child : children){
            RenderEntityHierarchy(*child);
        }

        ImGui::TreePop();
    }
}

void Engine::RenderStats(){
    ImGuiIO& io = ImGui::GetIO();
    ImGui::Text("Framerate:");
    ImGui::Text("Application average %.1f FPS", io.Framerate);

    static int counter = 0;
    ImGui::NewLine();
    ImGui::Text("Raytracings done = %d", counter);
    ImGui::NewLine();
    ImGui::Text("Frame to Raytrace: %d ", currentFrame);
    if(ImGui::Button("Raytrace")){
        //generate world at time t
        //i go through the scene graph and compute the right matrices for entities at time t
        std::vector<std::shared_ptr<Entity>> all_entities;
        //returns a list of all entities with positions (in canonical basis) at frame current frame
        //.get_all_entitities_updated(curFrame);
        engineWorld -> entity -> worldMatrix = engineWorld-> entity ->localMatrix;

        std::cerr<<"World matrix \n" << glm::to_string(engineWorld -> entity -> worldMatrix)<<std::endl;

        std::cerr<<"Local matrix \n" << glm::to_string(engineWorld -> entity -> localMatrix)<<std::endl;

        engineWorld->dfs_entitity_setup(currentFrame, all_entities, animate);

        std::cerr<<"World matrix after entity setup \n" << glm::to_string(engineWorld -> entity -> worldMatrix)<<std::endl;

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
        auto rayTracingCamera = std::make_shared<Camera>(600, 800, camera.getPosition());
        rayTracingCamera->lookat = camera.getPosition() + camera.direction;
        //rayTracingCamera->lookat = camera.getPosition() + camera.direction;
        //rayTracingCamera->vup = vec3(0, -1, 0);

        std::cerr<<"Camera is at : "<<glm::to_string(camera.getPosition())<<"\n";
        std::cerr<<"Camera direction is at : "<<glm::to_string(camera.direction)<<"\n";

        std::cerr<<"The world is at coord x: "<<worldRaytracer->get_boundingBox().get_ax(0).min<< " " << worldRaytracer->get_boundingBox().get_ax(0).max<<" \n";
        std::cerr<<"The world is at coord y: "<<worldRaytracer->get_boundingBox().get_ax(1).min<< " " << worldRaytracer->get_boundingBox().get_ax(1).max<<" \n";
        std::cerr<<"The world is at coord z: "<<worldRaytracer->get_boundingBox().get_ax(2).min<< " " << worldRaytracer->get_boundingBox().get_ax(2).max<<" \n";

        rayTracingCamera->render(worldRaytracer, "imageRender-frame.ppm");

        // rayTracingCamera = new Camera(height, width, camera.getPosition());
       // rayTracingCamera->render(world, "imageRender.ppm");
    }
}

void Engine::RenderHierarchy() {
    ImGui::Text("Entity Hierarchy View");
    // Render the hierarchy
    //additional argument of engine used for the engine.clicked
    RenderEntityHierarchy(*this->engineWorld /**this*/);
}

void Engine::RenderAnimation() {
    ImGui::Begin("Animation");

    ImGui::SliderInt("Animation Keyframe Panel", &currentFrame, 0, 2000, "Frame %d");

    // we want to have an animate condition
    if(ImGui::Button("Play")){
        animate = true;
    }

    ImGui::SameLine();


    if(ImGui::Button("Pause")){
        animate = false;
    }

    ImGui::SameLine();

    if (ImGui::Button("Set Keyframe")) {

        if(!animate){
            std::cout << "Keyframe added" << std::endl;
            engineWorld -> addKeyframe(currentFrame);
            markedPositions.push_back(currentFrame);
        }else{
            std::cout << "Cannot add frames during the animation" << std::endl;
        }
    }

    ImGui::NewLine();

    static int current_item = -1;

    if (ImGui::BeginCombo("Keyframe Dropdown Menu", "Keyframes")) {
        for (int i = 0; i < markedPositions.size(); i++) {

            bool is_selected = (current_item == i);
            if (ImGui::Selectable(std::to_string(markedPositions[i]).c_str(), is_selected)) {
                current_item = i;
                currentFrame = markedPositions[i];
            }

            if (is_selected) {
                ImGui::SetItemDefaultFocus();
            }
        }

        ImGui::EndCombo();
    }

    if(ImGui::Button("Delete Selected Keyframe")){
        if (current_item != -1) {
            markedPositions.erase(markedPositions.begin() + current_item);
        }
    }

    ImGui::SameLine();

    if (ImGui::Button("Delete All Keyframes")) {
        markedPositions.clear();
    }

    ImGui::End();
}

void Engine::RenderAddObject(){
    ImGui::Text("Here, you can add an object. Make sure \nthat the corresponding .obj file exists \nin the objects folder and input its name \nbelow!");
    ImGui::InputText("##objectName", objectName.buffer, sizeof(objectName.buffer));
    ImGui::NewLine();
    ImGui::Text("Here, add the texture you want to assign \nto the object! If no texture is provided, \nthe program will automatically assign \na default texture.");
    ImGui::InputText("##objectTexture", objectTexture.buffer, sizeof(objectTexture.buffer));
    ImGui::NewLine();
    ImGui::Text("Here, you may add a custom tag to the object");
    ImGui::InputText("##objectTag", objectTag.buffer, sizeof(objectTag.buffer));

    //temp
    ImGui::Text("Material: diel/dif ");
    ImGui::InputText("##objectMaterial", objectMaterial.buffer, sizeof(objectMaterial.buffer));

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

        //verify whether a texture was assigned, if not assign the grey texture
        if(textureString[0] == '\0')
            textureString = "Grey";

        std::string materialString(objectMaterial.buffer);

        std::string tagString;
        for (int i = 0; i < 256 && objectTag.buffer[i] != '\0'; ++i) {
            if (!std::isspace(static_cast<unsigned char>(objectTag.buffer[i]))) {
                tagString += objectTag.buffer[i];
            }
        }

        //verify whether a custom tag was assigned, if not assign a generic tag
        int numOfObjects = this -> engineWorld -> DFS();
        if(tagString[0] == '\0')
            tagString = "object " + std::to_string(numOfObjects);


        std::cout << SOURCE_DIR << std::endl;
        nameString = SOURCE_DIR + (std::string)"/objects/" + (std::string)nameString + (std::string)".obj";
        textureString = SOURCE_DIR + (std::string)"/Textures/" + (std::string)textureString + (std::string)".png";

        try {
            auto entity = std::make_shared<Entity>(nameString.c_str());
            entity -> texture = std::make_shared<Texture>(textureString.c_str());

            if(materialString == "diel")
                entity->material = std::make_shared<Dielectric>(0.999, 2);
            else
                entity->material = std::make_shared<DiffuseMaterial>();


            Node* node = new Node(entity);
            node -> setParent(this -> engineWorld);
            node->setName(tagString);

            // Update the newest node added to be the selected one
            selectedNode = node;

        } catch (const std::runtime_error& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }

        for(int i=0; i < 256; i++){
            objectName.buffer[i] = '\0';
            objectTexture.buffer[i] = '\0';
            objectTag.buffer[i] = '\0';
        }
    }
}
