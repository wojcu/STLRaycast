#include <algorithm>
#include <cassert>
#include <cmath>
#include <memory>
#include <mutex>
#include <thread>

#include "physics/collider.hpp"
#include "physics/collision_context.hpp"
#include "graphics/image.hpp"
#include "math/mat4.hpp"
#include "graphics/material.hpp"
#include "physics/plane_collider.hpp"
#include "graphics/point_light.hpp"
#include "physics/ray.hpp"
#include "graphics/render_context.hpp"
#include "graphics/scene.hpp"
#include "math/vec2.hpp"
#include "math/vec3.hpp"
#include "math/vec4.hpp"

class sphere_collider : public collider {
   public:
    sphere_collider(vec3 origin, double radius, material mat)
        : m_origin(std::move(origin)),
          m_radius(radius),
          m_material(std::move(mat)) {}

    vec3 &origin() { return m_origin; }

    const vec3 &origin() const { return m_origin; }

    double &radius() { return m_radius; }

    double radius() const { return m_radius; }

    material &object_material() { return m_material; }

    const material &object_material() const { return m_material; }

    collision_context collide(const ray &r) const override {
        collision_context result;
        result.valid() = false;
        const vec3 rdir = r.direction().normalized();
        const double quad_A = rdir.dot(rdir);
        const double quad_B = 2.0 * rdir.dot(r.start() - m_origin);
        const vec3 origin_offset = r.start() - m_origin;
        const double quad_C =
            origin_offset.dot(origin_offset) - m_radius * m_radius;
        const double delta = quad_B * quad_B - 4.0 * quad_A * quad_C;
        if (delta >= 0.0) {
            double t_1 = (-quad_B + std::sqrt(delta)) / (2.0 * quad_A);
            double t_2 = (-quad_B - std::sqrt(delta)) / (2.0 * quad_A);
            if (t_2 < t_1) {
                std::swap(t_1, t_2);
            }
            const double t_close = t_1 >= 0.0 ? t_1 : t_2;
            if (t_close >= 0.0) {
                result.valid() = true;
                result.fraction() = t_close;
                result.direction() = rdir;
                result.location() = r.start() + rdir * t_close;
                result.normal() = (result.location() - m_origin).normalized();
                result.hit_material() = m_material;
            }
        }
        return result;
    }

   private:
    vec3 m_origin;
    double m_radius;
    material m_material;
};

class menger_collider : public collider {
   public:
    menger_collider(vec3 origin, double radius, material mat)
        : m_origin(std::move(origin)),
          m_radius(radius),
          m_material(std::move(mat)) {}

    vec3 &origin() { return m_origin; }

    const vec3 &origin() const { return m_origin; }

    double &radius() { return m_radius; }

    double radius() const { return m_radius; }

    material &object_material() { return m_material; }

    const material &object_material() const { return m_material; }

    collision_context collide(const ray &r) const override {
        collision_context result;
        double rad = m_radius;
        vec3 orig = m_origin;
        sphere_collider parent(orig, rad, m_material);
        size_t max_iter = 5;
        result = sub_collide(r, parent, max_iter);
        if (result.valid() && result.fraction() > 0.0) {
            const vec3 color_base =
                (result.normal().normalized() + vec3(1.0, 1.0, 1.0)) / 2.0;
            result.hit_material().diffuse() = color_base;
            result.hit_material().specular() = vec3(1.0, 1.0, 1.0);
            result.hit_material().ambient() = color_base * 0.5;
            result.hit_material().shininess() = vec3(1.0, 1.0, 1.0) * 64.0;
            result.hit_material().reflectivity() = color_base * 0.5;
        }
        return result;
    }

   private:
    collision_context sub_collide(const ray &r, const sphere_collider &coll,
                                  size_t recurrsions) const {
        collision_context result;
        if (recurrsions == 0) {
            result = coll.collide(r);
        } else {
            const std::vector<vec3> offsets = {
                {1.0, 0.0, 0.0},  {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
                {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0},  {0.0, 0.0, -1.0}};
            std::vector<sphere_collider> children;
            for (const auto &off : offsets) {
                children.emplace_back(coll.origin() + off * coll.radius() / 2,
                                      coll.radius() / 2, m_material);
            }
            std::vector<std::pair<collision_context, size_t>> hits;
            for (size_t i = 0; i < children.size(); ++i) {
                collision_context col = children[i].collide(r);
                if (col.valid() && col.fraction() >= 0.0) {
                    hits.push_back({col, i});
                }
            }
            std::sort(hits.begin(), hits.end(),
                      [](const std::pair<collision_context, size_t> &a,
                         const std::pair<collision_context, size_t> &b) {
                          return a.first.fraction() < b.first.fraction();
                      });
            for (const auto &it : hits) {
                collision_context tmp =
                    sub_collide(r, children[it.second], recurrsions - 1);
                if (tmp.valid() && tmp.fraction() >= 0.0) {
                    result = tmp;
                    break;
                }
            }
        }
        return result;
    }

    vec3 m_origin;
    double m_radius;
    material m_material;
};

void printv(const vec3 &v) {
    printf("%.5lf, %.5lf, %.5lf", v.at(0), v.at(1), v.at(2));
}

void printv(const vec4 &v) {
    printf("%.5lf, %.5lf, %.5lf, %.5lf", v.at(0), v.at(1), v.at(2), v.at(3));
}

void build_easy_scene(scene &res, double aspect) {
    res.scene_camera().position() = vec3(0, 4, 4);
    res.scene_camera().target() = vec3(0, 0, 0);
    res.scene_camera().up() = vec3(0, 1, 0);
    res.scene_camera().v_fov() = 3.14159265 / 3.0;
    res.scene_camera().aspect() = aspect;
    res.scene_camera().z_near() = 1.0;
    res.scene_camera().z_far() = 16.0;

    material marble;
    marble.ambient() = vec3(0.5, 0.5, 0.5);
    marble.diffuse() = vec3(1.0, 1.0, 1.0);
    marble.specular() = vec3(1.0, 1.0, 1.0);
    marble.shininess() = vec3(1.0, 1.0, 1.0) * 64.0;
    marble.reflectivity() = vec3(1.0, 1.0, 1.0) * 0.5;
    vec3 colors[] = {{1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}};
    material marble_mats[3];
    for (size_t i = 0; i < 3; ++i) {
        marble_mats[i].ambient() = colors[i] * 0.5;
        marble_mats[i].diffuse() = colors[i];
        marble_mats[i].specular() = vec3(1.0, 1.0, 1.0);
        marble_mats[i].shininess() = vec3(1.0, 1.0, 1.0) * 64.0;
        marble_mats[i].reflectivity() = colors[i] * 0.5;
    }

    res.add_collider(std::unique_ptr<plane_collider>(
        new plane_collider(vec3(0, -2, 0), vec3(0, 1, 0), marble)));
    res.add_collider(std::unique_ptr<sphere_collider>(
        new sphere_collider(vec3(-1.5, 0, 1.5), 1, marble_mats[0])));
    res.add_collider(std::unique_ptr<sphere_collider>(
        new sphere_collider(vec3(1.5, 0, 1.5), 1, marble_mats[1])));
    res.add_collider(std::unique_ptr<menger_collider>(
        new menger_collider(vec3(1.5, 0, -1.5), 1, marble_mats[2])));
    point_light lt;
    lt.ambient() = vec3(0.1, 0.1, 0.1);
    lt.diffuse() = vec3(1.0, 1.0, 1.0);
    lt.specular() = vec3(1.0, 1.0, 1.0);
    lt.position() = vec3(-1.5, 0, -1.5);
    res.add_point_light(std::move(lt));
}

void build_easy_scene2(scene &res, double aspect) {
    res.scene_camera().position() = vec3(0.8, 1.6, 0.8);
    res.scene_camera().target() = vec3(0, 0, 0);
    res.scene_camera().up() = vec3(0, 1, 0);
    res.scene_camera().v_fov() = 3.14159265 / 3.0;
    res.scene_camera().aspect() = aspect;
    res.scene_camera().z_near() = 0.1;
    res.scene_camera().z_far() = 16.0;

    material marble;
    marble.ambient() = vec3(0.5, 0.5, 0.5);
    marble.diffuse() = vec3(1.0, 1.0, 1.0);
    marble.specular() = vec3(1.0, 1.0, 1.0);
    marble.shininess() = vec3(1.0, 1.0, 1.0) * 64.0;
    marble.reflectivity() = vec3(1.0, 1.0, 1.0) * 0.5;
    vec3 colors[] = {{1.0, 0.5, 0.5}, {0.5, 1.0, 0.5}, {0.5, 0.5, 1.0}};
    material marble_mats[3];
    for (size_t i = 0; i < 3; ++i) {
        marble_mats[i].ambient() = colors[i] * 0.5;
        marble_mats[i].diffuse() = colors[i];
        marble_mats[i].specular() = vec3(1.0, 1.0, 1.0);
        marble_mats[i].shininess() = vec3(1.0, 1.0, 1.0) * 64.0;
        marble_mats[i].reflectivity() = colors[i] * 0.5;
    }
    res.add_collider(std::unique_ptr<menger_collider>(
        new menger_collider(vec3(0, 0, 0), 1, marble)));
    point_light lt;
    lt.ambient() = vec3(0.1, 0.1, 0.1);
    lt.diffuse() = vec3(1.0, 1.0, 1.0);
    lt.specular() = vec3(1.0, 1.0, 1.0);
    lt.position() = vec3(0.1, 0.1, 0.1);
    res.add_point_light(std::move(lt));
}

class parallel_renderer {
   public:
    parallel_renderer(const render_context &context, const scene &sc,
                      size_t batch_size,
                      size_t workers = std::thread::hardware_concurrency()) {
        m_next_job = 0;
        m_jobs_count =
            std::ceil(double(context.screen_w()) / double(batch_size)) *
            std::ceil(double(context.screen_h()) / double(batch_size));
        m_result.resize(context.screen_w(), context.screen_h());
        std::vector<std::thread> threads;
        for (size_t i = 0; i < workers; ++i) {
            threads.emplace_back(std::thread([this, i, &context, &sc,
                                              batch_size]() {
                while (true) {
                    size_t j = get_job();
                    if (j >= m_jobs_count) {
                        break;
                    } else {
                        size_t horizontal_jobs = std::ceil(
                            double(m_result.width()) / double(batch_size));
                        size_t hor = j % horizontal_jobs;
                        size_t vert = j / horizontal_jobs;
                        size_t x_start = hor * batch_size;
                        size_t x_end =
                            std::min(x_start + batch_size, m_result.width());
                        size_t y_start = vert * batch_size;
                        size_t y_end =
                            std::min(y_start + batch_size, m_result.height());
                        for (size_t i = x_start; i < x_end; ++i) {
                            for (size_t j = y_start; j < y_end; ++j) {
                                double x_fac =
                                    double(i) / double(m_result.width() - 1);
                                double y_fac =
                                    1.0 -
                                    double(j) / double(m_result.height() - 1);
                                const vec2 fragment_offset(2.0 * x_fac - 1.0,
                                                           2.0 * y_fac - 1.0);
                                const vec3 frag = sc.render_fragment(
                                    fragment_offset, context);
                                m_result.at(i, j) =
                                    color(frag.at(0), frag.at(1), frag.at(2));
                            }
                        }
                    }
                }
            }));
        }
        for (size_t i = 0; i < workers; ++i) {
            threads[i].join();
        }
    }

    const image &result() const { return m_result; }

    image &result() { return m_result; }

   private:
    size_t get_job() {
        std::unique_lock<std::mutex> lock(m_mutex);
        size_t res = m_next_job;
        m_next_job += 1;
        return res;
    }

    image m_result;
    mutable std::mutex m_mutex;
    size_t m_next_job;
    size_t m_jobs_count;
};

void render_easy(const render_context &ctx) {
    image img;
    img.resize(ctx.screen_w(), ctx.screen_h());
    scene current_scene;
    build_easy_scene(current_scene, double(img.width()) / double(img.height()));
    for (size_t i = 0; i < img.width(); ++i) {
        for (size_t j = 0; j < img.height(); ++j) {
            double x_fac = double(i) / double(img.width() - 1);
            double y_fac = 1.0 - double(j) / double(img.height() - 1);
            const vec2 fragment_offset(2.0 * x_fac - 1.0, 2.0 * y_fac - 1.0);
            const vec3 frag =
                current_scene.render_fragment(fragment_offset, ctx);
            img.at(i, j) = color(frag.at(0), frag.at(1), frag.at(2));
        }
    }
    img.save("render.ppm");
}

void render_parallel(const render_context &ctx) {
    scene sc;
    build_easy_scene(sc, double(ctx.screen_w()) / double(ctx.screen_h()));
    parallel_renderer rend(ctx, sc, 32);
    rend.result().save("render.ppm");
}

int main(int argc, char *argv[]) {
    bool high_res = false;
    if (argc > 1 && std::string(argv[1]) == "high_res") {
        high_res = true;
    }
    render_context high;
    high.screen_w() = 1920;
    high.screen_h() = 1080;
    high.reflections() = 4;
    high.sample_count() = 8;
    render_context low;
    low.screen_w() = 640;
    low.screen_h() = 360;
    low.reflections() = 1;
    low.sample_count() = 1;
    render_context pick = low;
    if (high_res) {
        pick = high;
    }
    render_parallel(pick);
}
