#include "mat4.hpp"

#include <cmath>

mat4::mat4() { reset(); }

void mat4::reset() {
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            at(i, j) = 0.0;
        }
        at(i, i) = 1.0;
    }
}

double &mat4::at(size_t row, size_t col) { return m_data[4 * row + col]; }

double mat4::at(size_t row, size_t col) const { return m_data[4 * row + col]; }

void mat4::translate(const vec3 &pos) {
    mat4 tmp;
    for (size_t i = 0; i < 3; ++i) {
        tmp.at(i, 3) = pos.at(i);
    }
    *this = (*this) * tmp;
}

void mat4::rotate(double angle, const vec3 &axis) {
    mat4 result;
    result.fill(0.0);
    result.at(3, 3) = 1.0;
    double cos_a = std::cos(angle);
    double sin_a = std::sin(angle);
    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            result.at(i, j) = (1.0 - cos_a) * axis.at(i) * axis.at(j);
        }
    }
    for (size_t i = 0; i < 3; ++i) {
        result.at(i, i) += cos_a;
    }
    result.at(0, 1) += -axis.at(2) * sin_a;
    result.at(0, 2) += axis.at(1) * sin_a;
    result.at(1, 0) += axis.at(2) * sin_a;
    result.at(1, 2) += -axis.at(0) * sin_a;
    result.at(2, 0) += -axis.at(1) * sin_a;
    result.at(2, 1) += axis.at(0) * sin_a;
    *this = (*this) * result;
}

void mat4::scale(const vec3 &fac) {
    mat4 tmp;
    for (size_t i = 0; i < 3; ++i) {
        tmp.at(i, i) = fac.at(i);
    }
    *this = (*this) * tmp;
}

vec4 mat4::operator*(const vec4 &v) const {
    vec4 result;
    result.at(3) = 0;
    for (size_t i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.at(i) += at(i, j) * v.at(j);
        }
    }
    return result;
}

mat4 mat4::operator*(const mat4 &m) const {
    mat4 result;
    result.fill(0.0);
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            for (size_t k = 0; k < 4; ++k) {
                result.at(i, j) += at(i, k) * m.at(k, j);
            }
        }
    }
    return result;
}

void mat4::look_at(const vec3 &position, const vec3 &target, const vec3 &up) {
    vec3 n = (position - target).normalized();
    vec3 u = up.cross(n).normalized();
    vec3 v = n.cross(u);
    mat4 view;
    view.fill(0.0);
    for (size_t i = 0; i < 3; ++i) {
        view.at(0, i) = u.at(i);
        view.at(1, i) = v.at(i);
        view.at(2, i) = n.at(i);
    }
    view.at(3, 3) = 1.0;
    view.at(0, 3) = (-position).dot(u);
    view.at(1, 3) = (-position).dot(v);
    view.at(2, 3) = (-position).dot(n);
    *this = (*this) * view;
}

void mat4::perspective(double vfov, double aspect, double znear, double zfar) {
    mat4 proj;
    proj.fill(0.0);
    double f = 1.0 / std::tan(vfov / 2.0);
    proj.at(0, 0) = f / aspect;
    proj.at(1, 1) = f;
    proj.at(2, 2) = (zfar + znear) / (znear - zfar);
    proj.at(2, 3) = (2.0 * zfar * znear) / (znear - zfar);
    proj.at(3, 2) = -1.0;
    *this = (*this) * proj;
}

void mat4::fill(double value) {
    for (size_t i = 0; i < 4; ++i) {
        for (size_t j = 0; j < 4; ++j) {
            at(i, j) = value;
        }
    }
}
