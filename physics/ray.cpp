#include "ray.hpp"

ray::ray() {}

vec3 &ray::start() { return m_start; }

const vec3 &ray::start() const { return m_start; }

vec3 &ray::direction() { return m_direction; }

const vec3 &ray::direction() const { return m_direction; }

