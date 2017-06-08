#include "material.hpp"

material::material() {}

vec3 &material::specular() { return m_specular; }

const vec3 &material::specular() const { return m_specular; }

vec3 &material::diffuse() { return m_diffuse; }

const vec3 &material::diffuse() const { return m_diffuse; }

vec3 &material::ambient() { return m_ambient; }

const vec3 &material::ambient() const { return m_ambient; }

vec3 &material::shininess() { return m_shininess; }

const vec3 &material::shininess() const { return m_shininess; }

vec3 &material::reflectivity() { return m_reflectivity; }

const vec3 &material::reflectivity() const { return m_reflectivity; }
