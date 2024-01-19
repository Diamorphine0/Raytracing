#ifndef RAY_TRACING_Objects_LIST_H
#define RAY_TRACING_Objects_LIST_H

#include "Object.hpp"
#include "Utilities.hpp"
#include<unordered_set>
#include <vector>

/*
 * For now very basic class, stores as a list.
 * Could be improved for better query performance with k-d trees.
 *
 */
class Objects_List: public Object {
public:
    Objects_List(const std::unordered_set<std::shared_ptr<Object>> &init_objects);

    virtual bool hit(const Ray &r, const Interval &t,  HitRecord &rec) const;

    void add_object(std::shared_ptr<Object> obj);
    void remove_object(std::shared_ptr<Object> obj);

    std::vector<std::shared_ptr<Object>> get_list() const {return std::vector<std::shared_ptr<Object>>(objects_list.begin(), objects_list.end()); }

    void recompute_boundingBox();
private:
    std::unordered_set<std::shared_ptr<Object>> objects_list;
};


#endif //RAY_TRACING_Objects_LIST_H
