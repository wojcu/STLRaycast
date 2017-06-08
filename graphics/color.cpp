#include "color.hpp"

color::color(int red, int green, int blue) {
    m_components[0] = red;
    m_components[1] = green;
    m_components[2] = blue;
}

color::color() : color(0, 0, 0) {}

int &color::at(size_t index) {
    return m_components[index];
}

const int &color::at(size_t index) const {
    return m_components[index];
}

void color::clamp() {
    for (auto &v : m_components) {
        if (v < 0) {
            v = 0;
        } else if (v > 255) {
            v = 255;
        }
    }
}
