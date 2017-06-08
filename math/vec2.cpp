#include "vec2.hpp"

#include <cmath>

vec2::vec2(double x, double y) {
    m_components[0] = x;
    m_components[1] = y;
}

vec2::vec2() : vec2(0, 0) {}

double &vec2::at(size_t index) { return m_components[index]; }

double vec2::at(size_t index) const { return m_components[index]; }

vec2 vec2::operator*(double fac) const {
    return vec2(at(0) * fac, at(1) * fac);
}

vec2 vec2::operator-(const vec2 &other) const {
    return vec2(at(0) - other.at(0), at(1) - other.at(1));
}

vec2 vec2::operator+(const vec2 &other) const {
    return vec2(at(0) + other.at(0), at(1) + other.at(1));
}

vec2 vec2::operator/(double fac) const {
    return vec2(at(0) / fac, at(1) / fac);
}

vec2 vec2::operator*(const vec2 &other) const {
    return vec2(at(0) * other.at(0), at(1) * other.at(1));
}

vec2 vec2::operator-() const {
    return (*this) * (-1);
}

double vec2::length_squared() const {
    return m_components[0] * m_components[0] +
           m_components[1] * m_components[1];
}

double vec2::length() const { return std::sqrt(length_squared()); }

vec2 vec2::normalized() const { return *this / length(); }

double vec2::dot(const vec2 &other) const {
    vec2 tmp = (*this) * other;
    return tmp.at(0) + tmp.at(1);
}

double vec2::cross(const vec2 &other) const {
    return at(0) * other.at(1) - at(1) * other.at(0);
}
