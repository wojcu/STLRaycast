#include "scene.hpp"

#include <cmath>

#include "physics/collider.hpp"
#include "physics/plane_collider.hpp"

scene::scene() {}

void scene::add_collider(std::unique_ptr<collider> coll) {
    m_colliders.emplace_back(std::move(coll));
}

camera &scene::scene_camera() { return m_camera; }

const camera &scene::scene_camera() const { return m_camera; }

vec3 &scene::background() { return m_background; }

const vec3 &scene::background() const { return m_background; }

vec3 scene::render_sample(const vec2 &screen_offset, size_t reflections) const {
    ray pixel_ray;
    pixel_ray.start() = m_camera.map_from_screen(vec3(screen_offset, -1.0));
    const vec3 pixel_end = m_camera.map_from_screen(vec3(screen_offset, 1.0));
    pixel_ray.direction() = (pixel_end - pixel_ray.start()).normalized();
    collision_context hit = cast_ray(pixel_ray);
    vec3 total;
    vec3 contribution = vec3(1.0, 1.0, 1.0);
    while (hit.valid()) {
        total = total +
                (/*render_point_lights(hit) +*/ render_phong(hit)) * contribution *
                    (vec3(1.0, 1.0, 1.0) - hit.hit_material().reflectivity());
        contribution = contribution * hit.hit_material().reflectivity();
        if (reflections > 0) {
            const vec3 hit_normal = hit.normal().normalized();
            const vec3 hit_reflection =
                hit_normal.reflect(-hit.direction().normalized());
            ray reflected_ray;
            reflected_ray.direction() = hit_reflection.normalized();
            reflected_ray.start() =
                hit.location() + reflected_ray.direction() * 0.001;
            hit = cast_ray(reflected_ray);
            reflections -= 1;
        } else {
            hit.valid() = false;
        }
    }
    return total * 255.0;
}

vec3 scene::render_fragment(const vec2 &screen_pos,
                            const render_context &ctx) const {
    vec3 result;
    if (ctx.sample_count() != 0) {
        if (ctx.sample_count() == 1) {
            result = render_sample(screen_pos, ctx.reflections());
        } else {
            vec3 total;
            double weight = 0.0;
            for (size_t i = 0; i < ctx.sample_count() - 1; ++i) {
                for (size_t j = 0; j < ctx.sample_count() - 1; ++j) {
                    vec2 part(double(i) / double(ctx.sample_count() - 1),
                              double(j) / double(ctx.sample_count() - 1));
                    part = part * 2.0 - vec2(1, 1);
                    const double part_len = part.length();
                    part = part * ctx.multisample_delta();
                    vec3 sample =
                        render_sample(screen_pos + part, ctx.reflections());
                    const double sample_weight =
                        std::exp(-part_len * part_len / 2.0) /
                        std::sqrt(2.0 * 3.14159265);
                    weight += sample_weight;
                    total = total + sample * sample_weight;
                }
            }
            result = total / weight;
        }
    }
    return result;
}

void scene::add_point_light(point_light l) {
    m_lights.emplace_back(std::move(l));
}

collision_context scene::cast_ray(const ray &r) const {
    collision_context hit;
    for (const auto &coll : m_colliders) {
        const collision_context cctx = coll->collide(r);
        if (cctx.valid() && cctx.fraction() >= 0.0 &&
            cctx.fraction() < m_camera.z_far()) {
            if (!hit.valid()) {
                hit = cctx;
            } else {
                if (cctx.fraction() < hit.fraction()) {
                    hit = cctx;
                }
            }
        }
    }
    return hit;
}

vec3 scene::render_point_lights(const collision_context &ctx) const {
    vec3 total;
    ray pixel_ray;
    pixel_ray.direction() = ctx.direction();
    pixel_ray.start() = ctx.location() - ctx.direction() * ctx.fraction();
    for (const auto &l : m_lights) {
        const vec3 lpnormal = -ctx.direction();
        const material no_mat;
        const plane_collider lplane(l.position(), lpnormal, no_mat);
        const collision_context lpctx = lplane.collide(pixel_ray);
        const vec3 attenuation(1, 8, 8);
        if (lpctx.valid() && lpctx.fraction() >= 0.0) {
            if (lpnormal.dot(ctx.location()) < 0.0) {
                const double ldi = (lpctx.location() - l.position()).length();
                total = total +
                        vec3(1.0, 1.0, 1.0) /
                            (attenuation.at(0) + attenuation.at(1) * ldi +
                             attenuation.at(2) * ldi * ldi);
            }
        }
    }
    return total;
}

vec3 scene::render_phong(const collision_context &ctx) const {
    vec3 total;
    for (const auto &l : m_lights) {
        ray light_ray;
        light_ray.start() = l.position();
        light_ray.direction() =
            (ctx.location() - light_ray.start()).normalized();
        const collision_context lctx = cast_ray(light_ray);
        const material &mt = ctx.hit_material();
        total = total + mt.ambient() * l.ambient();
        if (lctx.valid() &&
            (lctx.location() - ctx.location()).length() < 0.000001) {
            const vec3 to_light = (l.position() - ctx.location()).normalized();
            const vec3 hit_normal = ctx.normal().normalized();
            const vec3 to_viewer = -ctx.direction().normalized();
            const vec3 to_reflection =
                to_light +
                (hit_normal * hit_normal.dot(to_light) - to_light) * 2.0;
            const double diff_fac = to_light.dot(hit_normal);
            if (diff_fac > 0.0) {
                total = total + mt.diffuse() * l.diffuse() * diff_fac;

                const double spec_fac = to_reflection.dot(to_viewer);
                if (spec_fac > 0.0) {
                    total = total +
                            mt.specular() * l.specular() *
                                vec3(std::pow(spec_fac, mt.shininess().at(0)),
                                     std::pow(spec_fac, mt.shininess().at(1)),
                                     std::pow(spec_fac, mt.shininess().at(2)));
                }
            }
        }
    }
    return total;
}
