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

    bool contains(float x) const{
        return min <= x && x <= max;
    }

    bool surrounds(float x) const{
        return min < x && x < max;
    }

    float get_min() const { return min; }
    float get_max() const { return max;}

private:
    float min, max;
};


#endif //RAY_TRACING_INTERVAL_H
