// Here we will implement the ECS class.
#include "Engine.h"
#include "Utilities.hpp"
#include "scenegraph.h"
#include <memory>
#include "TriangleMesh.h"

Engine::Engine(engineCamera camera, const std::string &shader_path): width(width), height(height), camera(camera){

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

}

void Engine::update(Shader* shader){

    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    ImGui::SetNextWindowSize(ImVec2((this->width)/ 6 , (this->height)*3/8));
    ImGui::SetNextWindowPos(ImVec2 (0,0));
    ImGui::Begin("Hierarchy");

    RenderHierarchy();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2((this->width)/3 * 2, (this->height) *3/4));
    ImGui::SetNextWindowPos(ImVec2 ((this->width) / 6, 0));
    ImGui::Begin("Engine Visualization");
    LoadEngine();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2((this->width)/ 6 , (this->height)*3/8));
    ImGui::SetNextWindowPos(ImVec2 (0,(this->height)*3/8));
    ImGui::Begin("Properties");
    RenderProperties();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2((this->width)/ 6 , (this->height)*3/8));
    ImGui::SetNextWindowPos(ImVec2 ((this->width) * 5 / 6,0));
    ImGui::Begin("Settings");
    RenderStats();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2((this->width),(this->height) / 4));
    ImGui::SetNextWindowPos(ImVec2 (0,(this->height) * 3 / 4));
    ImGui::Begin("Animation");
    RenderAnimation();
    ImGui::End();

    ImGui::SetNextWindowSize(ImVec2((this->width)/ 6 , (this->height)*3/8));
    ImGui::SetNextWindowPos(ImVec2((this->width) * 5 / 6, (this->height) * 3 / 8));
    ImGui::Begin("Add Object");
    RenderAddObject();
    ImGui::End();

    // Rendering
    ImGui::Render();

    fb -> Bind();

    if(animate){
        camera.animationPrep(engineWorld);
        big_grid.draw(*shaderLine, camera);
        axes.draw(*shaderAx, camera);
        camera.animateScene(engineWorld, *shader, currentFrame);
    }
    else{
        camera.Clear();
        big_grid.draw(*shaderLine, camera);
        axes.draw(*shaderAx, camera);
    }

    //big_grid.draw(*shaderLine, camera);
    //axes.draw(*shaderAx, camera);

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
        //here we would want to used the engine.clicked as well!!!
        //this->clicked->entity->translate(translationX, translationY, translationZ);
        //this->clicked->entity->scale(scale, scale, scale);

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

void RenderEntityHierarchy(Node& node /* Engine engine*/) {
    bool isClicked = ImGui::TreeNodeEx(node.name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
    if(isClicked){
        //for now context menu is irrelevant
        // Context menu when right-clicking an entity
        /*
        if (ImGui::BeginPopupContextItem()) {
            if (ImGui::MenuItem("Delete Entity")) {
                // Implement logic to delete the entity
            }
            if (ImGui::MenuItem("Create Child")) {
                // Implement logic to create a child entity
            }
            ImGui::EndPopup();
        }
        */

        //at this point this node is clicked so we can set the engine.clicked var, but htis variable doesnt work
        //engine.clicked = &node;

        // Render child entities recursively
        std::vector<Node*> children = node.getChildren();
        for (auto child : children){
            RenderEntityHierarchy(*child /*engine*/ );
        }

        // End the tree node
        ImGui::TreePop();
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

    // we should have buttons to stop and play the animation

    //static int coarseFrame = 0;
    ImGui::SliderInt("Coarse Slider", &currentFrame, 0, 2000, "Frame %d");

    // we want to have an animate condition
    if(ImGui::Button("Play")){
        animate = true;
    }

    if(ImGui::Button("Pause")){
        animate = false;
    }

    if (ImGui::Button("Mark Position")) {
        // Add the keyframe
        engineWorld ->addKeyframe(currentFrame);

        markedPositions.push_back(currentFrame);
    }

    if (ImGui::Button("Clear All Marks")) {
        markedPositions.clear();
    }

    ImGui::Text("Coarse Frame: %d", currentFrame);

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

void Engine::RenderAddObject(){
    ImGui::Text("Here, you can add an object. Make sure \nthat the corresponding .obj file exists \nin the objects folder and input its name \nbelow!");
    ImGui::InputText("##objectName", objectName.buffer, sizeof(objectName.buffer));
    ImGui::Text("Here, add the texture you want to assign \nto the object! If no texture is provided, \nthe program will automatically assign \na default texture.");
    ImGui::InputText("##objectTexture", objectTexture.buffer, sizeof(objectTexture.buffer));
    ImGui::Text("Here, you may add a custom tag to the object");
    ImGui::InputText("##objectTag", objectTag.buffer, sizeof(objectTag.buffer));


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
            textureString = "Grey.png";


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
        nameString = SOURCE_DIR + (std::string)"/objects/" + (std::string)nameString;
        textureString = SOURCE_DIR + (std::string)"/Textures/" + (std::string)textureString;

        try {
            auto entity = std::make_shared<Entity>(nameString.c_str());
            entity -> texture = new Texture(textureString.c_str());

            Node* node = new Node(entity);
            node -> setParent(this -> engineWorld);
            node->setName(tagString);
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
