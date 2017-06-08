#ifndef VEC3_HPP
#define VEC3_HPP

#include <array>
#include "vec2.hpp"

class vec3 {
   public:
    vec3(double x, double y, double z);
    vec3(const vec2 &v, double z);
    vec3();
    double &at(size_t index);
    double at(size_t index) const;
    vec3 operator*(double fac) const;
    vec3 operator-(const vec3 &other) const;
    vec3 operator+(const vec3 &other) const;
    vec3 operator/(double fac) const;
    vec3 operator*(const vec3 &other) const;
    vec3 operator-() const;
    double length_squared() const;
    double length() const;
    vec3 normalized() const;
    double dot(const vec3 &other) const;
    vec3 cross(const vec3 &other) const;
    vec3 reflect(const vec3 &other) const;

   private:
    std::array<double, 3> m_components;
};

#endif  // VEC3_HPP
