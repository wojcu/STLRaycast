#include "collision_context.hpp"

collision_context::collision_context() : m_valid(false) {}

bool collision_context::valid() const { return m_valid; }

bool &collision_context::valid() { return m_valid; }

double collision_context::fraction() const { return m_fraction; }

double &collision_context::fraction() { return m_fraction; }

const vec3 &collision_context::normal() const { return m_normal; }

vec3 &collision_context::normal() { return m_normal; }

material &collision_context::hit_material() { return m_hit_material; }

const material &collision_context::hit_material() const {
    return m_hit_material;
}

vec3 &collision_context::direction() { return m_direction; }

const vec3 &collision_context::direction() const { return m_direction; }

vec3 &collision_context::location() { return m_location; }

const vec3 &collision_context::location() const { return m_location; }
