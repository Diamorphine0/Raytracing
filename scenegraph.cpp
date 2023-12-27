#include "scenegraph.h"

Node::Node(): entity(nullptr), parent(nullptr), children({}){}
Node::Node(Entity* entity): entity(entity), parent(nullptr), children({}){}
Node::Node(Entity* entity, Node* parent): entity(entity), parent(parent), children({}){}
Node::Node(Entity* entity, Node* parent, std::vector<Node*> children): entity(entity), parent(parent), children(children){}

void Node::setParent(Node* newParent){

    if(parent != nullptr)
        (parent -> children).erase(std::remove((parent -> children).begin(), (parent -> children).end(), parent), (parent -> children).end());

    if (newParent != nullptr) {
        (newParent -> children).push_back(this);
    }

    this -> parent = newParent;
}

void Node::updateWorldMatrix(){

    if((parent -> entity -> worldMatrix) != glm::mat4())
        (entity -> worldMatrix) = (parent -> entity -> worldMatrix) * (entity -> localMatrix);
    else
        (entity -> worldMatrix) = (entity -> localMatrix);

    // we can then draw everything relative to the main matrix

    for(auto child: children){
        child -> updateWorldMatrix();
    }

}

void Node::Draw(const Shader& shader){

    if(entity != nullptr){
        const VertexArray& va = *(entity -> getVA());

        entity -> scale(0.5, 0.5, 1);

        entity -> rotate(0, 0, 0.01);

        std::cout << "Draw Function" << std::endl;
        shader.Bind();
        std::cout << "Shader Binded" << std::endl;

        // take care of when the parent is null
        if(parent != nullptr){
            if(parent -> entity != nullptr){
                if((parent -> entity -> worldMatrix) != glm::mat4())
                    (entity -> worldMatrix) = (parent -> entity -> worldMatrix) * (entity -> localMatrix);
                else
                    (entity -> worldMatrix) = (entity -> localMatrix);
            }
            else{
                (entity -> worldMatrix) = (entity -> localMatrix);
            }
        }

        GLuint MatrixID = glGetUniformLocation(shader.getID(), "Transform");
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(entity -> worldMatrix)[0][0]);

        std::cout << "VA Binded " << va.getID() << std::endl;
        va.Bind();
        // the size should be stored in the va ...
        glDrawArrays(GL_TRIANGLES, 0, 6);
        std::cout << "Displayed to Screen" << std::endl;
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    for(auto child: children){
        child -> Draw(shader);
    }
}
