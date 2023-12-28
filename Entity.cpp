#include "Entity.h"

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

void VertexArray::AddBuffer(const VertexBuffer* vb, const VertexBufferLayout& layout){

    Bind();

    vb -> Bind();

    // we get vertex buffer elements
    const auto& elements = layout.GetElements();

    unsigned int offset = 0;

    for(unsigned int i = 0; i < elements.size(); i++){

        const auto& element = elements[i];

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(
            0,
            element.count,      // size
            element.type,       // type
            element.normalized ? GL_TRUE : GL_FALSE, // normalized?
            sizeof(Vertex),     // stride - THAT MAY BE WRONG!
            (const void*) 0     // array buffer offset
            );

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            element.count,                    // size
            element.type,                     // type
            element.normalized ? GL_TRUE : GL_FALSE, // normalized?
            sizeof(Vertex),                   // stride - THAT MAY BE WRONG!
            (void*) offsetof(Vertex, Color)   // array buffer offset
            );

        // offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
    }

}

// This should be a template

Entity::Entity(){
    va = new VertexArray();
}

Entity::Entity(std::vector<Vertex>& vertices){

    va = new VertexArray();

    va -> Bind();

    VertexBuffer* vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push<Vertex>(3);

    va -> AddBuffer(vb, layout);
}

Entity::Entity(const char* path){

    std::vector<Vertex> vertices = {};
    std::vector< glm::vec2 > uvs;
    std::vector< glm::vec3 > normals;

    std::cout << "Before loading" << std::endl;
    loadOBJ(path, vertices, uvs, normals);
    std::cout << "After loading" << std::endl;

    va = new VertexArray();

    va -> Bind();

    std::cout << "Size" << vertices.size() << std::endl;

    VertexBuffer* vb = new VertexBuffer(&vertices[0], vertices.size() * sizeof(Vertex));

    VertexBufferLayout layout;

    layout.Push<Vertex>(3);

    va -> AddBuffer(vb, layout);
};

bool Entity::loadOBJ(const char * path,
                     std::vector < Vertex > & out_vertices,
                     std::vector < glm::vec2 > & out_uvs,
                     std::vector < glm::vec3 > & out_normals){

    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;

    std::vector< Vertex > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;

    FILE* file = fopen(path, "r");
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

            //should use something like emplace back
            temp_vertices.push_back(Vertex(vertex, glm::vec3(color,  color,  color)));

        }
        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y );
            temp_uvs.push_back(uv);}
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

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){
        unsigned int vertexIndex = vertexIndices[i];
        Vertex vertex = temp_vertices[ vertexIndex - 1];
        out_vertices.push_back(vertex);
        std::cout << vertex.Coordinates.x << " " << vertex.Coordinates.y << " " << vertex.Coordinates.z << std::endl;
    }

    std::cout << "Size: " << out_vertices.size() << std::endl;
}

// We want to extend the entity functionality to load objects.
// To store the animations -> Basically every element should know it's movement in each frame
// it suffices to store triangles (in 3s and the normals -)
