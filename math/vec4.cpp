#include "vec4.hpp"

#include <cmath>

vec4::vec4(double x, double y, double z, double w) {
    m_components[0] = x;
    m_components[1] = y;
    m_components[2] = z;
    m_components[3] = w;
}

vec4::vec4(const vec3 &v, double w) : vec4(v.at(0), v.at(1), v.at(2), w) {}

vec4::vec4(const vec2 &v, double z, double w) : vec4(v.at(0), v.at(1), z, w) {}

vec4::vec4() : vec4(0, 0, 0, 1) {}

double &vec4::at(size_t index) { return m_components[index]; }

double vec4::at(size_t index) const { return m_components[index]; }

vec4 vec4::operator*(double fac) const {
    return vec4(at(0) * fac, at(1) * fac, at(2) * fac, at(3) * fac);
}

vec4 vec4::operator-(const vec4 &other) const {
    return vec4(at(0) - other.at(0), at(1) - other.at(1), at(2) - other.at(2),
                at(3) - other.at(3));
}

vec4 vec4::operator+(const vec4 &other) const {
    return vec4(at(0) + other.at(0), at(1) + other.at(1), at(2) + other.at(2),
                at(3) + other.at(3));
}

vec4 vec4::operator/(double fac) const {
    return vec4(at(0) / fac, at(1) / fac, at(2) / fac, at(3) / fac);
}

vec4 vec4::operator*(const vec4 &other) const {
    return vec4(at(0) * other.at(0), at(1) * other.at(1), at(2) * other.at(2),
                at(3) * other.at(3));
}

vec4 vec4::operator-() const { return (*this) * (-1); }

double vec4::length_squared() const {
    return m_components[0] * m_components[0] +
           m_components[1] * m_components[1] +
           m_components[2] * m_components[2] +
           m_components[3] * m_components[3];
}

double vec4::length() const { return std::sqrt(length_squared()); }

vec4 vec4::normalized() const { return *this / length(); }

double vec4::dot(const vec4 &other) const {
    vec4 tmp = (*this) * other;
    return tmp.at(0) + tmp.at(1) + tmp.at(2) + tmp.at(3);
}

vec3 vec4::to_affine() const { return vec3(at(0), at(1), at(2)) / at(3); }
