#include "scenegraph.h"
#include "texture.h"

Node::Node(): entity(nullptr), parent(nullptr), children({}){}
Node::Node(Entity* entity): entity(entity), parent(nullptr), children({}){}
Node::Node(Entity* entity, Node* parent): entity(entity), parent(parent), children({}){}
Node::Node(Entity* entity, Node* parent, std::vector<Node*> children): entity(entity), parent(parent), children(children){}

void Node::setParent(Node* newParent){
    //Reassigning parents doesnt work
    //    if(parent != nullptr)
//        //(parent -> children).erase(std::remove((parent -> children).begin(), (parent -> children).end(), parent), (parent -> children).end());

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

        // we need to rely on key frames
        // we need to calculate the interpolation between the key frames
        // how can we store the key frame data -> ie the transform of each object and the timestamp?
        // here we should be calling the per second node animation

        entity -> rotate(0.01f, 0.001f, 0.001f, 1);

        // we check the current time in the animation and see in between which 2 keyframes we are
        // then we do the rotation, scaling and transformation according to the point in the interpolation

        // basically here we set the local matrix transformation -> This should be done relative to the previous timeframe matrix.

        // for rotation we can use quaternions.

        // we want to be able to decompose a matrix. -> Potentially better to just store the decomposition ?

        // Can we assume no projective component ?

        // we can easily compute the interpolation matricies.

        // what is the point of the scene graph -> Just to get the relations

        // we then get that

        shader.Bind();

        // take care of when the parent is null

        // This is the animation step
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

        // check if the texture is loaded (we should not be initializing a new texture every frame).
        Texture texture("../Raytracing/Textures/texture.png");
        texture.Bind();
        // why are we setting a uniform for the texture ?

        // what value do we want to pass to it ?
        shader.SetUniform1i("u_Texture", 1);

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, 10000);
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    for(auto child: children){
        child -> Draw(shader);
    }
}
