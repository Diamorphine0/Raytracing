//
// Created by tudor on 14/12/23.
//

#include "Hittable_List.h"
#include<limits.h>
void Hittable_List::add_object(Hittable *obj) {
    objects_list.insert(obj);
}

void Hittable_List::remove_object(Hittable *obj) {
    if(objects_list.count(obj)){
        objects_list.erase(obj);
    }
}

std::pair<bool, Hittable *> Hittable_List::intersectWithRay(const Ray &r, float &t) const {
    std::cerr<<"curent list: "<<objects_list.size()<<"\n";
    t = FLT_MAX;
    std::pair<bool, Hittable *> ans;
    for(auto object: objects_list){
        float new_t;
        auto new_ans = object->intersectWithRay(r, new_t);
        if(new_ans.first && new_t < t){
            ans = new_ans;
            t = new_t;
        }
    }
    return ans;
}

Hittable_List::~Hittable_List() {
    for(auto obj:objects_list)
        delete obj;
}

