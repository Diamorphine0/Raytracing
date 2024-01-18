#ifndef RAY_TRACING_Objects_LIST_H
#define RAY_TRACING_Objects_LIST_H

#include "Objects.hpp"
#include "Utilities.hpp"
#include<unordered_set>

/*
 * For now very basic class, stores as a list.
 * Could be improved for better query performance with k-d trees.
 *
 */
class Objects_List: public Objects {
public:
    Objects_List(const std::unordered_set<std::shared_ptr<Objects>> &init_objects): objects_list(init_objects) {}

    virtual bool hit(const Ray &r, const Interval &t,  HitRecord &rec) const;

    void add_object(std::shared_ptr<Objects> obj);
    void remove_object(std::shared_ptr<Objects> obj);

private:
    std::unordered_set<std::shared_ptr<Objects>> objects_list;
};


#endif //RAY_TRACING_Objects_LIST_H
