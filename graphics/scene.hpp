#ifndef SCENE_HPP
#define SCENE_HPP

#include <memory>
#include <vector>
#include "camera.hpp"
#include "physics/collider.hpp"
#include "math/vec3.hpp"
#include "render_context.hpp"
#include "point_light.hpp"
#include "physics/collision_context.hpp"

class scene {
   public:
    scene();
    void add_collider(std::unique_ptr<collider> coll);
    void add_point_light(point_light l);
    camera &scene_camera();
    const camera &scene_camera() const;
    vec3 &background();
    const vec3 &background() const;
    vec3 render_fragment(const vec2 &screen_pos,
                          const render_context &ctx) const;
    collision_context cast_ray(const ray &r) const;

   private:
    vec3 render_sample(const vec2 &screen_pos, size_t reflections) const;
    vec3 render_point_lights(const collision_context &ctx) const;
    vec3 render_phong(const collision_context &ctx) const;

    camera m_camera;
    std::vector<std::unique_ptr<collider>> m_colliders;
    std::vector<point_light> m_lights;
    vec3 m_background;
};

#endif  // SCENE_HPP
