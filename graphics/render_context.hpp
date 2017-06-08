#ifndef RENDER_CONTEXT_HPP
#define RENDER_CONTEXT_HPP

#include "math/vec2.hpp"

class render_context {
   public:
    render_context();
    size_t screen_w() const;
    size_t &screen_w();
    size_t screen_h() const;
    size_t &screen_h();
    vec2 multisample_delta() const;
    size_t sample_count() const;
    size_t &sample_count();
    size_t &reflections();
    size_t reflections() const;

   private:
    size_t m_sample_count;
    size_t m_screen_w;
    size_t m_screen_h;
    size_t m_reflections;
};

#endif  // RENDER_CONTEXT_HPP
