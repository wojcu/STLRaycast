#include "plane_collider.hpp"

#include <cmath>

plane_collider::plane_collider(vec3 origin, vec3 normal, material mat)
    : m_origin(std::move(origin)),
      m_normal(std::move(normal)),
      m_material(std::move(mat)) {}

vec3 &plane_collider::origin() { return m_origin; }

const vec3 &plane_collider::origin() const { return m_origin; }

vec3 &plane_collider::normal() { return m_normal; }

const vec3 &plane_collider::normal() const { return m_normal; }

material &plane_collider::object_material() { return m_material; }

const material &plane_collider::object_material() const { return m_material; }

collision_context plane_collider::collide(const ray &r) const {
    collision_context result;
    const vec3 normal = m_normal.normalized();
    const vec3 rdir = r.direction().normalized();
    const double parallel_factor = normal.dot(rdir);
    const double eps = 0.0000001;
    result.valid() = false;
    if (std::abs(parallel_factor) > eps) {
        const double fraction =
            (m_origin - r.start()).dot(normal) / parallel_factor;
        if (fraction >= 0.0) {
            result.fraction() = fraction;
            result.direction() = rdir;
            result.valid() = true;
            result.normal() = normal;
            result.location() = rdir * result.fraction() + r.start();
            if (normal.dot(r.start() - m_origin) < 0.0) {
                result.normal() = -normal;
            }
            result.hit_material() = m_material;
        }
    }
    return result;
}
