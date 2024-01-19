//
// Created by tudor on 14/12/23.
//

#include "Objects_List.h"
#include<limits.h>
void Objects_List::add_object(std::shared_ptr<Object> obj) {
    boundingBox = AxisAlignedBoundingBox(boundingBox, obj->get_boundingBox());
    objects_list.insert(obj);
}

/**
 * Call recompute if you remove a lot of objects.
 * @param obj
 */
void Objects_List::remove_object(std::shared_ptr<Object> obj) {
    if(objects_list.count(obj)){
        objects_list.erase(obj);
    }
}

bool Objects_List::hit(const Ray &r, const Interval &t,  HitRecord &rec) const{
    HitRecord tempRec;
    bool hit = false;
    auto closest = t.max;
    for(const auto &object: objects_list){
        if(object->hit(r, Interval(t.min, closest), tempRec)){
            closest = tempRec.tHit;
            rec = tempRec;
            hit = true;
        }
    }
    return hit;
}

Objects_List::Objects_List(const std::unordered_set<std::shared_ptr<Object>> &init_objects) {
    for(auto &x: init_objects){
        add_object(x);
    }
}

void Objects_List::recompute_boundingBox() {
    boundingBox =AxisAlignedBoundingBox();
    for(auto &x: objects_list){
        boundingBox = AxisAlignedBoundingBox(boundingBox, x->get_boundingBox());
    }
}


