#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <vector>

#include "color.hpp"

class image {
   public:
    image();
    void resize(size_t width, size_t height);
    color &at(size_t x, size_t y);
    const color &at(size_t x, size_t y) const;
    void load(const std::string &filename);
    void save(const std::string &filename) const;
    size_t width() const;
    size_t height() const;

   private:
    size_t m_width, m_height;
    std::vector<color> m_data;
};

#endif  // IMAGE_HPP
