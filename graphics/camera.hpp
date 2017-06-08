#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "math/mat4.hpp"
#include "math/vec3.hpp"

class camera {
   public:
    camera();
    vec3 &position();
    const vec3 &position() const;
    vec3 &target();
    const vec3 &target() const;
    vec3 &up();
    const vec3 &up() const;
    double &aspect();
    double aspect() const;
    double &v_fov();
    double v_fov() const;
    double &z_near();
    double z_near() const;
    double &z_far();
    double z_far() const;
    vec3 map_from_screen(const vec3 &v) const;
    mat4 view_matrix() const;
    mat4 projection_matrix() const;

   private:
    vec3 m_position;
    vec3 m_target;
    vec3 m_up;
    double m_aspect;
    double m_v_fov;
    double m_z_near;
    double m_z_far;
};

#endif  // CAMERA_HPP
