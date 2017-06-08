#ifndef COLOR_HPP
#define COLOR_HPP

#include <array>

class color {
   public:
    color(int red, int green, int blue);
    color();
    int &at(size_t index);
    const int &at(size_t index) const;
    void clamp();

   private:
    std::array<int, 3> m_components;
};

#endif  // COLOR_HPP
