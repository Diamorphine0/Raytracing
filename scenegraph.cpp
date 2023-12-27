#include "scenegraph.h"

SceneGraph::SceneGraph()
{
    // Should contain a top node
}

void Node::setParent(Node* parent){

    // remove from parent
    if (this->parent){
        // remove the element from the vertex
        ((this->parent) -> children).erase(
            std::remove(((this->parent) -> children).begin(), ((this->parent) -> children).end(), (this -> parent)),
            ((this->parent) -> children).end());
    }

    if (parent) {
        (parent -> children).push_back(this);
    }

    this -> parent = parent;
}


void updateWorldMatrix(glm::vec4& parentWorldMatrix){

    auto isNotEqualToZero = [](glm::mat4& matrix) {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (matrix[i][j] != 0.0f) {
                    return true;
                }
            }
        }
        return false;
    };

// C

// Check that the parent matrix is not equal to the identity matrix

//    if (isNotEqualToZero(parentWorldMatrix)) {
//        worldMatrix = parentWorldMatrix * localMatrix;
//    } else {
//        worldMatrix = localMatrix;
//    }

//    // For each of the children, update their world matrix respectively
//    for (auto child : children) {
//        child->updateWorldMatrix(worldMatrix);
//    }

}
