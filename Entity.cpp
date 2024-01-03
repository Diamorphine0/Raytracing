#include "Entity.h"
#include <cstring>

Entity::Entity(const char* path){
    //load the data
    loadOBJ(path);
    //sanity check: is the obj well loaded.
    printOBJToFile("log.txt");
    addColor();
    setup();
};

void Entity::setup(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh.size() * sizeof(Vertex), &mesh[0], GL_STATIC_DRAW);


    //experiment: colorification.
    //vertex coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    //vertex uvs
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    //vertex normals
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normals));

    //vertex colors
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, colors));
}

void Entity::loadOBJ(const char * path){
    FILE* file = fopen(path, "r");

    //error message
    if( file == NULL ){
        printf("Impossible to open the file !\n");
        return;
    }

    std::vector<glm::vec3> coordinates;
    std::vector<glm::vec2> uv;
    std::vector<glm::vec3> normals;
    std::cout << "loading initiated" << std::endl;

    while( 1 ){
        char lineHeader[256];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);

        if (res == EOF)
            break;

        //coordinates
        if ( strcmp( lineHeader, "v" ) == 0 ){
            glm::vec3 vertex_coordinates;
            fscanf(file, "%f %f %f\n", &vertex_coordinates.x, &vertex_coordinates.y, &vertex_coordinates.z );
            coordinates.push_back(vertex_coordinates);
        }

        else if ( strcmp( lineHeader, "vt" ) == 0 ){
            glm::vec2 vertex_uv;
            fscanf(file, "%f %f\n", &vertex_uv.x, &vertex_uv.y );
            uv.push_back(vertex_uv);
        }

        else if ( strcmp( lineHeader, "vn" ) == 0 ){
            glm::vec3 vertex_normals;
            fscanf(file, "%f %f %f\n", &vertex_normals.x, &vertex_normals.y, &vertex_normals.z );
            normals.push_back(vertex_normals);
        }

        else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser : ( Try exporting with other options\n");
                return;
            }

            Vertex v0;
            v0.coordinates = coordinates[vertexIndex[0] - 1];
            v0.uv = uv[uvIndex[0] - 1];
            v0.normals = normals[normalIndex[0] - 1];

            Vertex v1;
            v1.coordinates = coordinates[vertexIndex[1] - 1];
            v1.uv = uv[uvIndex[1] - 1];
            v1.normals = normals[normalIndex[1] - 1];

            Vertex v2;
            v2.coordinates = coordinates[vertexIndex[2] - 1];
            v2.uv = uv[uvIndex[2] - 1];
            v2.normals = normals[normalIndex[2] - 1];

            mesh.push_back(v0);
            mesh.push_back(v1);
            mesh.push_back(v2);
        }
    }
    std::cout << "loading terminated" << std::endl;
    return;
}

void Entity::addTexture(const char* path){
    pTexture = new Texture(GL_TEXTURE_2D, path);
    if( !pTexture->Load())
        return;

    pTexture -> Bind(GL_TEXTURE0);
    glUniform1i(gSamplerLocation, 0);
}

void Entity::addColor(){
    for(auto v : mesh){
        //we just like blue for now!
        v.colors = glm::vec3(0.0f, 0.0f, 1.0f);
    }
}

void Entity::printOBJToFile(const std::string& filename) {
    // Open the file for writing
    std::ofstream outputFile(filename);

    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (auto v : mesh) {
        // Write data to the file
        outputFile << v.coordinates.x << " " << v.coordinates.y << " " << v.coordinates.z << std::endl;
        outputFile << v.uv.x << " " << v.uv.y << std::endl;
        outputFile << v.normals.x << " " << v.normals.y << " " << v.normals.z << std::endl;
        outputFile << std::endl;
    }

    // Close the file
    outputFile.close();
}

// We want to extend the entity functionality to load objects.
// To store the animations -> Basically every element should know it's movement in each frame
// it suffices to store triangles (in 3s and the normals -)
