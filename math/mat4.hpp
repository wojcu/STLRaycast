#ifndef MAT4_HPP
#define MAT4_HPP

#include <array>

#include "vec4.hpp"
#include "vec3.hpp"

class mat4 {
   public:
    mat4();
    void reset();
    double &at(size_t row, size_t col);
    double at(size_t row, size_t col) const;
    void translate(const vec3 &pos);
    void rotate(double angle, const vec3 &axis);
    void scale(const vec3 &fac);
    vec4 operator*(const vec4 &v) const;
    mat4 operator*(const mat4 &m) const;
    void look_at(const vec3 &position, const vec3 &target, const vec3 &up);
    void perspective(double vfov, double aspect, double znear, double zfar);
    void fill(double value = 0.0);

   private:
    std::array<double, 16> m_data;
};

#endif  // MAT4_HPP
