#include "Entity.h"
#include <cstring>
VertexBuffer::VertexBuffer(const void* data, unsigned long size){
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    std::cout << "Initialized" << std::endl;
}

VertexBuffer::~VertexBuffer(){
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const {
    std::cout << "Binded" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexArray::VertexArray(){
    std::cout << "Entity created" << std::endl;
    glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray(){
    glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::Bind() const{
    glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind() const{
    glBindVertexArray(0);
}

enum Attribute {POS, COLOR, UV, NORM};

void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout& layout){

    Bind();

    vb -> Bind();

    // we get vertex buffer elements
    const auto& elements = layout.GetElements();

    unsigned int offset = 0;

//    for(unsigned int i = 0; i < elements.size(); hit++){

//        const auto& element = elements[hit];

        // the first attribute is the position
        glEnableVertexAttribArray(POS);
        glVertexAttribPointer(
            0,
            3,      // size
            GL_FLOAT,       // type
            GL_FALSE, // normalized?
            sizeof(Vertex),     // stride - THAT MAY BE WRONG!
            (const void*) 0     // array buffer offset
        );

        // the second attribute is color -> This is not always going to happen
        glEnableVertexAttribArray(COLOR);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                    // size
            GL_FLOAT,                     // type
            GL_FALSE, // normalized?
            sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*) offsetof(Vertex, Color)   // array buffer offset
        );

        // we need to use the object UVs
        glEnableVertexAttribArray(UV);
        glVertexAttribPointer(
            // this sets the name
            2,
            2, // size
            GL_FLOAT, // type
            GL_FALSE, // normalized?
            sizeof(Vertex), // stride - THAT MAY BE WRONG!
            (void*) offsetof(Vertex, UV)  // array buffer offset
        );

        glEnableVertexAttribArray(NORM);
        glVertexAttribPointer(
            3,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(Vertex),
            (void*) offsetof(Vertex, Norm)
            );
//    }

}

// This should be a template

Entity::Entity(){
    va = new VertexArray();
}

Entity::Entity(std::vector<Vertex>& vertices){

    this -> vertices = vertices;

    va = new VertexArray();

    va -> Bind();

    VertexBuffer* vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push_Vertex(3);

    va -> AddBuffer(vb, layout);

    // we furthermore want to allocate a unique id to it that we will use for coloring (we need to maintain a dictionary associating its pointer and id).
}

Entity::Entity(std::string path){

    std::vector<Vertex> vertices = {};
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    // we might as well just pass the vertices without uvs.
    loadOBJ(path, vertices, uvs, normals);

    this -> vertices = vertices;

    va = new VertexArray();

    va -> Bind();

    std::cout << "Size" << vertices.size() << std::endl;

    VertexBuffer* vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push_Vertex(3);

    va -> AddBuffer(vb, layout);
};

bool Entity::loadOBJ(std::string path,
                     std::vector < Vertex > & out_vertices,
                     // we want to store the uvs;
                     // they have to also somehow be passed to opengl;
                     std::vector < glm::vec2 > & out_uvs,
                     std::vector < glm::vec3 > & out_normals){

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    std::vector< Vertex > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    FILE* file = fopen(path.c_str(), "r");
    std::cout << file << std::endl;
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return false;
    }

    float color = 0.1f;
    while( 1 ){

        color += 0.01;
        if (color >= 1.0f) color = 0;
        char lineHeader[256];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF)
            break;

        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );

            std::cout << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;

            // no need to create a vertex object here come to think of it
            temp_vertices.push_back(Vertex(vertex, glm::vec3(color,  color,  color)));
        }

        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);

            // we want to store the uvs; - do we associate one to every ... ?
            // basically we want to store the uvs in the layout ...
        }
        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
            temp_normals.push_back(normal);
        }
        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }
    }

    std::cout << "Vert size: " << temp_vertices.size() << std::endl;
    std::cout << "UV size: " << temp_uvs.size() << std::endl;

    // the same way that we are going through the vertexIndicies
    // we have to go through the uv inidices and put all of this shit into a vertex
    // we don't really care about the normals ?

    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        unsigned int vertexIndex = vertexIndices[i];
        Vertex vertex = temp_vertices[ vertexIndex - 1];

        out_vertices.push_back(vertex);
        // we likewise want to push the uvs
        std::cout << vertex.Coordinates.x << " " << vertex.Coordinates.y << " " << vertex.Coordinates.z << std::endl;
    }

    // now we simply iterate through the uv coordinates and append them to the texture -> ideally we just want to add to the definitions of the verticies.
    std::cout << "Loading uvIndicies size" << uvIndices.size() << std::endl;
    for( unsigned int i=0; i < uvIndices.size(); i++ ){

        unsigned int uvIndex = uvIndices[i];

        auto uv = temp_uvs[uvIndex - 1];

        out_vertices[i].UV = uv;
    }

    std::cout << "Loading normals size" << normalIndices.size() << std::endl;
    for( unsigned int i=0; i < normalIndices.size(); i++ ){

        unsigned int normalIndex = normalIndices[i];

        auto norm = temp_normals[normalIndex - 1];

        out_vertices[i].Norm = norm;
    }

    return true;
}

// Make sure there is no projective component.

void Entity::interpolate(int currentFrame){

    if(currentFrame > keyFrameFinalTime or currentFrame < keyFrameInitialTime)
        return;

    auto idx = index(currentFrame, 0, keyFrames.size() - 1);

    auto& startTime = keyFrames[idx].first;
    auto& startFrame = keyFrames[idx].second;
    auto& finalTime = keyFrames[idx+1].first;
    auto& finalFrame = keyFrames[idx+1].second;

    float t = (float)(currentFrame - startTime)/(finalTime - startTime);

    //quaternions
    glm::quat startRot = glm::quat_cast(startFrame);
    glm::quat finalRot = glm::quat_cast(finalFrame);

    glm::quat curRot = glm::slerp(startRot, finalRot, t);

    localMatrix = glm::mat4_cast(curRot);

    // we can do a more precise interpolation ... (using Bezier curves instead).
    localMatrix[3] = startFrame[3] * (1 - t) + finalFrame[3] * t;
}
