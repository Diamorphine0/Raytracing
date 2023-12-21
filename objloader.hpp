#pragma once
#include "glm/fwd.hpp"
#include <vector>

#ifndef OBJLOADER_HPP
#define OBJLOADER_HPP

class ObjectLoader {
public:
    bool load_object(
        const char* path,
        std::vector<glm::vec3>& out_vertices
        //std::vector<glm::vec2>& out_uvs,
        //std::vector<glm::vec3>& out_normals
        );
};


#endif
