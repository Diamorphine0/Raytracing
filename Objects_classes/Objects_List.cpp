//
// Created by tudor on 14/12/23.
//

#include "Objects_List.h"
#include<limits.h>
void Objects_List::add_object(std::shared_ptr<Objects> obj) {
    objects_list.insert(obj);
}

void Objects_List::remove_object(std::shared_ptr<Objects> obj) {
    if(objects_list.count(obj)){
        objects_list.erase(obj);
    }
}

bool Objects_List::hit(const Ray &r, const Interval &t,  HitRecord &rec) const{
    HitRecord tempRec;
    bool hit = false;
    auto closest = t.get_max();
    for(const auto &object: objects_list){
        if(object->hit(r, Interval(t.get_min(), closest), tempRec)){
            closest = tempRec.tHit;
            rec = tempRec;
            hit = true;
        }
    }
    return hit;
}


