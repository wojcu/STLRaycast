#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "math/vec3.hpp"

class material {
   public:
    material();

    vec3 &specular();
    const vec3 &specular() const;
    vec3 &diffuse();
    const vec3 &diffuse() const;
    vec3 &ambient();
    const vec3 &ambient() const;
    vec3 &shininess();
    const vec3 &shininess() const;
    vec3 &reflectivity();
    const vec3 &reflectivity() const;

   private:
    vec3 m_specular;
    vec3 m_diffuse;
    vec3 m_ambient;
    vec3 m_shininess;
    vec3 m_reflectivity;
};

#endif  // MATERIAL_HPP
