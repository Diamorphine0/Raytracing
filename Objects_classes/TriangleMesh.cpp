//
// Created by tudor on 20/01/24.
//

#include "TriangleMesh.h"
#include "Triangle.h"
#include <vector>
bool TriangleMesh::hit(const Ray &r, const Interval &restriction, HitRecord &rec) const {
    return triangles->hit(r, restriction, rec);
}

TriangleMesh::TriangleMesh(const std::shared_ptr<Entity> &e) {
    std::vector<std::shared_ptr<Object>> triang;
    for(int i = 0; i < e->vertices.size(); i+= 3){
        std::vector<point3> coords(3);
        vec3 normal_mean = {0, 0, 0};
        color3 color_mean = {0, 0, 0};
        for(auto j = 0; j < 3; j ++){
            auto &vertex = e->vertices[j + i];
            auto modified = glm::vec3(e->worldMatrix * glm::vec4(vertex.Coordinates, 1));
            coords[j] = glm::vec3(modified);
            //normal_mean +=  glm::vec3(e->worldMatrix * glm::vec4(vertex.Norm, 0));
            color_mean += vertex.Color;
        }

        //normal_mean *= 1.0/3;
        color_mean *= 1.0/3;

        auto new_triangle = std::make_shared<Triangle>(coords[0], coords[1], coords[2], glm::abs(glm::ballRand(1.0f)));
        triang.push_back(new_triangle);
    }
    triangles = std::make_shared<BVH_Node>(triang, 0, triang.size());
    boundingBox = triangles->get_boundingBox();
}