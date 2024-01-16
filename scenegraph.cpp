#include "scenegraph.h"

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

        // this would happen every time
      //  entity -> rotate(0.01f, 0.001f, 0.001f, 1);

        //std::cout << "Draw Function" << std::endl;
        shader.Bind();
        //std::cout << "Shader Binded" << std::endl;

        // take care of when the parent is null
        if(parent != nullptr){
            //std::cout << "Are we here ?" << std::endl;
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

        //std::cout << "here" << std::endl;

        //std::cout << shader.getID() << std::endl;

        GLuint MatrixID = glGetUniformLocation(shader.getID(), "Transform");

        //std::cout << MatrixID << std::endl;

        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(entity -> worldMatrix)[0][0]);

        //std::cout << "VA Binded " << va.getID() << std::endl;
        va.Bind();
        // This is really bad !!!
        glDrawArrays(GL_TRIANGLES, 0, 10000);
        //std::cout << "Displayed to Screen" << std::endl;
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    for(auto child: children){
        //std::cout << "Child drawn" << std::endl;
        child -> Draw(shader);
    }
}

std::pair<bool, Hittable*> Node::intersectWithRay(const Ray &r, float &t) const {
    t = FLT_MAX;
    std::pair<bool, Hittable *> ans = {false, NULL};
    if(entity != nullptr){
        //std::cerr<<"Not null entity\n";
        ans = entity->hl->intersectWithRay(r, t);
    }
    if(!ans.first)
        t = FLT_MAX;
    for(auto child: children){
        float new_t;
        auto new_ans = child->intersectWithRay(r, new_t);
        if(!new_ans.first || new_t < EPS)
            continue;
        if(new_t < t){
            ans = new_ans;
            t = new_t;
        }
    }
    return ans;
}
//
//void Node::Concatenate(Hittable_List* cumul_hl){
//
//    if(entity != nullptr){
//        (cumul_hl -> objects_list).insert(entity -> hl -> objects_list.begin(), entity -> hl -> objects_list.end());
//    }
//
//    for(auto child: children){
//        child -> Concatenate(cumul_hl);
//    }
//
//}
