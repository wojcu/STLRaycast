#include "point_light.hpp"

point_light::point_light() {}

vec3 &point_light::position() { return m_position; }

const vec3 &point_light::position() const { return m_position; }

vec3 &point_light::ambient() { return m_ambient; }

const vec3 &point_light::ambient() const { return m_ambient; }

vec3 &point_light::diffuse() { return m_diffuse; }

const vec3 &point_light::diffuse() const { return m_diffuse; }

vec3 &point_light::specular() { return m_specular; }

const vec3 &point_light::specular() const { return m_specular; }
