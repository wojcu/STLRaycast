#include "camera.hpp"

#include <cmath>

camera::camera() {}

vec3 &camera::position() { return m_position; }

const vec3 &camera::position() const { return m_position; }

vec3 &camera::target() { return m_target; }

const vec3 &camera::target() const { return m_target; }

vec3 &camera::up() { return m_up; }

const vec3 &camera::up() const { return m_up; }

double &camera::aspect() { return m_aspect; }

double camera::aspect() const { return m_aspect; }

double &camera::v_fov() { return m_v_fov; }

double camera::v_fov() const { return m_v_fov; }

double &camera::z_near() { return m_z_near; }

double camera::z_near() const { return m_z_near; }

double &camera::z_far() { return m_z_far; }

double camera::z_far() const { return m_z_far; }

vec3 camera::map_from_screen(const vec3 &v) const {
    const vec3 n_up = m_up.normalized();
    const vec3 n_dir = (m_target - m_position).normalized();
    const vec3 x_dir = -n_up.cross(n_dir).normalized();
    const vec3 y_dir = x_dir.cross(n_dir).normalized();
    const double expand = std::tan(m_v_fov / 2.0) * m_z_near;
    const vec3 pixel_world = n_dir * m_z_near +
                             x_dir * m_aspect * v.at(0) * expand +
                             y_dir * v.at(1) * expand;
    const double cam_to_px_len = pixel_world.length();
    const double depth =
        2.0 * m_z_far * cam_to_px_len /
        (m_z_far + m_z_near - v.at(2) * m_z_far + v.at(2) * m_z_near);
    vec3 result = m_position + pixel_world.normalized() * depth;
    return result;
}

mat4 camera::view_matrix() const {
    mat4 res;
    res.look_at(m_position, m_target, m_up);
    return res;
}

mat4 camera::projection_matrix() const {
    mat4 res;
    res.perspective(m_v_fov, m_aspect, m_z_near, m_z_far);
    return res;
}
