#include "render_context.hpp"

render_context::render_context()
    : m_sample_count(1), m_screen_w(0), m_screen_h(0), m_reflections(4) {}

size_t &render_context::screen_h() { return m_screen_h; }

size_t render_context::screen_h() const { return m_screen_h; }

size_t &render_context::screen_w() { return m_screen_w; }

size_t render_context::screen_w() const { return m_screen_w; }

vec2 render_context::multisample_delta() const {
    return vec2(1.0 / double(m_screen_w), 1.0 / double(m_screen_h));
}

size_t render_context::sample_count() const { return m_sample_count; }

size_t &render_context::sample_count() { return m_sample_count; }

size_t &render_context::reflections() { return m_reflections; }

size_t render_context::reflections() const { return m_reflections; }
