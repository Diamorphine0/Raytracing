#ifndef RAY_TRACING_HITTABLE_LIST_H
#define RAY_TRACING_HITTABLE_LIST_H

#include "Hittable.hpp"
#include<unordered_set>

/*
 * For now very basic class, stores as a list.
 * Could be improved for better query performance with k-d trees.
 *
 * TODO: be careful with pointers and deleting them from memory/ using modern cpp
 */
class Hittable_List: public Hittable {
public:
    Hittable_List(const std::unordered_set<Hittable*> &init_objects): objects_list(init_objects) {}
    Hittable_List() : Hittable_List(std::unordered_set<Hittable*>(0)) {}
    /*
     * Deleting the world list of objects deletes the objects as well. - maybe not the best idea but for now should work
     */
    ~Hittable_List();

    virtual std::pair<bool, Hittable*> intersectWithRay(const Ray &r, float &t) const;
    virtual float getFacingRatio(const Ray &r) const {return (float) 0;}

    void add_object(Hittable* obj);
    void remove_object(Hittable* obj);

private:
    std::unordered_set<Hittable*> objects_list;
};


#endif //RAY_TRACING_HITTABLE_LIST_H
