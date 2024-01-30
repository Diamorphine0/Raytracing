#include "scenegraph.h"
#include "Texture.h"

Node::Node(): entity(nullptr), parent(nullptr), children({}){}
Node::Node(const std::shared_ptr<Entity> &entity): entity(entity), parent(nullptr), children({}){}
Node::Node(const std::shared_ptr<Entity> &entity, Node* parent): entity(entity), parent(parent), children({}){}
Node::Node(const std::shared_ptr<Entity> &entity, Node* parent, const std::vector<Node*> &children): entity(entity), parent(parent), children(children){}

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

    for(auto child: children){
        child -> updateWorldMatrix();
    }

}

void Node::Draw(const Shader& shader, glm::vec3 pos, int& currentFrame){

//    if(entity != nullptr){
        const VertexArray& va = *(entity -> getVA());

       //entity -> rotate(0.01f, 0.001f, 0.01f, 1);

        shader.Bind();

        entity -> localMatrix = entity -> getClosestKeyframe(currentFrame);

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

        GLuint MatrixModelID = glGetUniformLocation(shader.getID(), "ModelMatrix");
        GLuint MatrixID = glGetUniformLocation(shader.getID(), "Transform");
        GLuint viewPosID = glGetUniformLocation(shader.getID(), "viewPos");

        glUniform3fv(viewPosID, 1, &pos[0]);
        glUniformMatrix4fv(MatrixModelID, 1, GL_FALSE, &(glm::inverse(getModelMatrix()) * entity -> worldMatrix)[0][0]);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(entity -> worldMatrix)[0][0]);

        if(entity -> texture != nullptr){
            entity -> texture -> Bind();
        }

        shader.SetUniform1i("u_Texture", 0);

        va.Bind();
        // This can be fixed as soon as we store the verticies ...
        glDrawArrays(GL_TRIANGLES, 0, entity -> vertices.size());
        glClear(GL_DEPTH_BUFFER_BIT);
//    }

    for(auto child: children){
        child -> Draw(shader, pos, currentFrame);
    }
}

void Node::addKeyframe(int time){
    // we assume that the process is fast enough that all the matricies will remain unchanged throughout
//    if(entity != nullptr){

        if(time < (entity -> keyFrameInitialTime)){
            std::cout << "Are we adding keyframes already" << std::endl;
            entity -> keyFrameInitialTime = time;
        }
        if(time > entity -> keyFrameFinalTime){
            std::cout << "Are we adding keyframes already" << std::endl;
            entity -> keyFrameFinalTime = time;
        }
        std::pair entityKeyframe(time, (entity -> localMatrix));
        entity -> keyFrames.push_back(entityKeyframe);

    for(auto child: children){
        child->addKeyframe(time);
    }

}

void Node::Animate(const Shader& shader, int currentFrame){

    if(entity != nullptr){

        const VertexArray& va = *(entity -> getVA());

        // The interpolation finds the desired local transformation matrix (relative to the intial verticies stored in the buffer - they remain unchanged).
        entity -> interpolate(currentFrame);

        shader.Bind();

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

        if(entity -> texture != nullptr)
            entity -> texture -> Bind();

        shader.SetUniform1i("u_Texture", 0);

        va.Bind();
        glDrawArrays(GL_TRIANGLES, 0, entity -> vertices.size());
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    for(auto child: children){
        child -> Animate(shader, currentFrame);
    }
}

glm::mat4 Node::getModelMatrix(){
    if(parent == nullptr){
        return entity -> worldMatrix;
    }
    return parent -> getModelMatrix();
}


/**
 * Remember to remove nodes
 */
Node::~Node() {
    for(auto &x:children)
        delete x;
}
/**
 * Adds only entities WHICH HAVE AT LEAST ONE VERTICE
 */
void Node::dfs_entitity_setup(int currentFrame, std::vector<std::shared_ptr<Entity>> &entities, bool animate) {

    if(entity != nullptr) {
//        if(animate)
//            entity->interpolate(currentFrame);

        if (parent != nullptr) {
            if (parent->entity != nullptr) {
                if ((parent->entity->worldMatrix) != glm::mat4())
                    (entity->worldMatrix) = (parent->entity->worldMatrix) * (entity->localMatrix);
                else
                    (entity->worldMatrix) = (entity->localMatrix);
            } else {
                (entity->worldMatrix) = (entity->localMatrix);
            }
        }
        if(!entity->vertices.empty())
            entities.push_back(entity);
    }
    for(auto child: children){
        child -> dfs_entitity_setup(currentFrame, entities, animate);
    }
}

int Node::DFS(){
    int res = 1;
    for(Node* child : children){
        res += child->DFS();
    }
    return res;
}

