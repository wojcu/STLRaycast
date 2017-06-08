#ifndef VEC2_HPP
#define VEC2_HPP

#include <array>

class vec2 {
   public:
    vec2(double x, double y);
    vec2();
    double &at(size_t index);
    double at(size_t index) const;
    vec2 operator*(double fac) const;
    vec2 operator-(const vec2 &other) const;
    vec2 operator+(const vec2 &other) const;
    vec2 operator/(double fac) const;
    vec2 operator*(const vec2 &other) const;
    vec2 operator-() const;
    double length_squared() const;
    double length() const;
    vec2 normalized() const;
    double dot(const vec2 &other) const;
    double cross(const vec2 &other) const;

   private:
    std::array<double, 2> m_components;
};

#endif  // VEC2_HPP
