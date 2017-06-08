#ifndef COLLISION_CONTEXT_HPP
#define COLLISION_CONTEXT_HPP

#include "graphics/material.hpp"
#include "math/vec3.hpp"

class collision_context {
   public:
    collision_context();
    bool valid() const;
    bool &valid();
    double fraction() const;
    double &fraction();
    const vec3 &normal() const;
    vec3 &normal();
    material &hit_material();
    const material &hit_material() const;
    vec3 &direction();
    const vec3 &direction() const;
    vec3 &location();
    const vec3 &location() const;
    

   private:
    bool m_valid;
    double m_fraction;
    vec3 m_normal;
    material m_hit_material;
    vec3 m_direction;
    vec3 m_location;
};

#endif  // COLLISION_CONTEXT_HPP
