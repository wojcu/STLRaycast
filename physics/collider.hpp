#ifndef COLLIDER_HPP
#define COLLIDER_HPP

#include "ray.hpp"
#include "collision_context.hpp"

class collider {
   public:
    collider(); 
    virtual ~collider(); 
    virtual collision_context collide(const ray &r) const = 0;
};

#endif // COLLIDER.HPP
