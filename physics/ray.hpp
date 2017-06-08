#ifndef RAY_HPP
#define RAY_HPP

#include "math/vec3.hpp"

class ray {
   public:
    ray();
    vec3 &start();
    const vec3 &start() const;
    vec3 &direction();
    const vec3 &direction() const;
    size_t &jumps();
    
   private:
    vec3 m_start;
    vec3 m_direction;
};

#endif  // RAY_HPP
