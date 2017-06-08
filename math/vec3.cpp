#include "vec3.hpp"

#include <cmath>

vec3::vec3(double x, double y, double z) {
    m_components[0] = x;
    m_components[1] = y;
    m_components[2] = z;
}

vec3::vec3(const vec2 &v, double z) : vec3(v.at(0), v.at(1), z) {}

vec3::vec3() : vec3(0, 0, 0) {}

double &vec3::at(size_t index) { return m_components[index]; }

double vec3::at(size_t index) const { return m_components[index]; }

vec3 vec3::operator*(double fac) const {
    return vec3(at(0) * fac, at(1) * fac, at(2) * fac);
}

vec3 vec3::operator-(const vec3 &other) const {
    return vec3(at(0) - other.at(0), at(1) - other.at(1), at(2) - other.at(2));
}

vec3 vec3::operator+(const vec3 &other) const {
    return vec3(at(0) + other.at(0), at(1) + other.at(1), at(2) + other.at(2));
}

vec3 vec3::operator/(double fac) const {
    return vec3(at(0) / fac, at(1) / fac, at(2) / fac);
}

vec3 vec3::operator*(const vec3 &other) const {
    return vec3(at(0) * other.at(0), at(1) * other.at(1), at(2) * other.at(2));
}

vec3 vec3::operator-() const { return (*this) * (-1); }

double vec3::length_squared() const {
    return m_components[0] * m_components[0] +
           m_components[1] * m_components[1] +
           m_components[2] * m_components[2];
}

double vec3::length() const { return std::sqrt(length_squared()); }

vec3 vec3::normalized() const { return *this / length(); }

double vec3::dot(const vec3 &other) const {
    vec3 tmp = (*this) * other;
    return tmp.at(0) + tmp.at(1) + tmp.at(2);
}

vec3 vec3::cross(const vec3 &other) const {
    vec3 result(at(1) * other.at(2) - at(2) * other.at(1),
                at(2) * other.at(0) - at(0) * other.at(2),
                at(0) * other.at(1) - at(1) * other.at(0));
    return result;
}

vec3 vec3::reflect(const vec3 &other) const {
    vec3 norm = normalized();
    return (norm * norm.dot(other) - other) * 2 + other;
}
