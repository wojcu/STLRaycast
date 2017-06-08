#ifndef VEC4_HPP
#define VEC4_HPP

#include <array>
#include "vec2.hpp"
#include "vec3.hpp"

class vec4 {
   public:
    vec4(double x, double y, double z, double w);
    vec4(const vec3 &v, double w);
    vec4(const vec2 &v, double z, double w);
    vec4();
    double &at(size_t index);
    double at(size_t index) const;
    vec4 operator*(double fac) const;
    vec4 operator-(const vec4 &other) const;
    vec4 operator+(const vec4 &other) const;
    vec4 operator/(double fac) const;
    vec4 operator*(const vec4 &other) const;
    vec4 operator-() const;
    double length_squared() const;
    double length() const;
    vec4 normalized() const;
    double dot(const vec4 &other) const;
    vec3 to_affine() const;

   private:
    std::array<double, 4> m_components;
};

#endif  // VEC4_HPP
