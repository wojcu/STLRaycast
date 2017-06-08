#include "image.hpp"

#include <fstream>

image::image() {}

void image::resize(size_t width, size_t height) {
    m_width = width;
    m_height = height;
    m_data.resize(m_width * m_height);
}

color &image::at(size_t x, size_t y) { return m_data[y * m_width + x]; }

const color &image::at(size_t x, size_t y) const { return at(x, y); }

void image::load(const std::string &) {
    //TODO
}

void image::save(const std::string &filename) const {
    std::ofstream file(filename);
    file << "P3" << std::endl;
    file << m_width << " " << m_height << std::endl;
    file << "255" << std::endl;
    for (const auto &c_raw : m_data) {
        color c = c_raw;
        c.clamp();
        file << c.at(0) << " " << c.at(1) << " " << c.at(2) << " ";
    }
    file << "\n";
}

size_t image::width() const {
    return m_width;
}

size_t image::height() const {
    return m_height;
}
