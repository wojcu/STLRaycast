#ifndef POINT_LIGHT_HPP
#define POINT_LIGHT_HPP

#include "math/vec3.hpp"

class point_light {
   public:
    point_light();
    vec3 &position();
    const vec3 &position() const;
    vec3 &ambient();
    const vec3 &ambient() const;
    vec3 &diffuse();
    const vec3 &diffuse() const;
    vec3 &specular();
    const vec3 &specular() const;

   private:
    vec3 m_position;
    vec3 m_ambient;
    vec3 m_diffuse;
    vec3 m_specular;
};

#endif  // POINT_LIGHT_HPP
