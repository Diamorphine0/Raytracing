//
// Created by tudor on 20/01/24.
//

#include "TriangleMesh.h"

bool TriangleMesh::hit(const Ray &r, const Interval &restriction, HitRecord &rec) const {
    return triangles->hit(r, restriction, rec);
}

TriangleMesh::TriangleMesh(const Entity &e) {
    auto objects = std::make_shared<Objects_List>();
    for(int i = 0; i < e.vertices.size(); i+= 3){
        for(auto j = i; j < i + 3; j ++){
            auto &vertex = e.vertices[j];
            auto position = e.worldMatrix * glm::vec4(vertex.Coordinates, 0);
            auto normal = vertex.Norm;
        }
    }

}
