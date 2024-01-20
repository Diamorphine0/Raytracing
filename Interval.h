//
// Created by tudor on 18/01/24.
//

#ifndef RAY_TRACING_INTERVAL_H
#define RAY_TRACING_INTERVAL_H
#include "Utilities.hpp"

class Interval {
public:
    Interval() : min(INF), max(-INF) {}
    Interval(float _min, float _max) : min(_min), max(_max) {}
    Interval(const Interval &a, const Interval &b) : min(std::min(a.min, b.min)), max(std::max(a.max, b.max)) {}

    bool contains(float x) const{
        return min <= x && x <= max;
    }

    bool surrounds(float x) const{
        return min < x && x < max;
    }

    Interval expand(float delta) const {
        auto padding = delta/2;
        return {min - padding, max + padding};
    }


    bool min_compare( const Interval &b) const{
        return min < b.min;
    }


    bool max_compare( const Interval &b) const{
        return max < b.max;
    }

    float min, max;
};


#endif //RAY_TRACING_INTERVAL_H
