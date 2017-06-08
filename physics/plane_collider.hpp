#ifndef PLANE_COLLIDER_HPP
#define PLANE_COLLIDER_HPP

#include "collider.hpp"
#include "graphics/material.hpp"

class plane_collider : public collider {
   public:
    plane_collider(vec3 origin, vec3 normal, material mat);
    vec3 &origin();
    const vec3 &origin() const;
    vec3 &normal();
    const vec3 &normal() const;
    material &object_material();
    const material &object_material() const;
    collision_context collide(const ray &r) const override;

   private:
    vec3 m_origin;
    vec3 m_normal;
    material m_material;
};

#endif  // PLANE_COLLIDER_HPP
