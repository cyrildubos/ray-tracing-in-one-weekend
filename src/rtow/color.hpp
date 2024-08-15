#pragma once

#include <cmath>

#include "interval.hpp"
#include "pixel.hpp"

namespace rtow {
class color {
private:
  double m_r = 0.0;
  double m_g = 0.0;
  double m_b = 0.0;

public:
  color() : m_r(0.0), m_g(0.0), m_b(0.0) {}

  color(double p_r, double p_g, double p_b) : m_r(p_r), m_g(p_g), m_b(p_b) {}

  double r() const { return m_r; }
  double g() const { return m_g; }
  double b() const { return m_b; }

  rtow::pixel to_pixel() {
    rtow::interval intensity(0.000, 0.999);

    return {static_cast<std::uint8_t>(256.0 * intensity.clamp(m_r)),
            static_cast<std::uint8_t>(256.0 * intensity.clamp(m_g)),
            static_cast<std::uint8_t>(256.0 * intensity.clamp(m_b))};
  }

  static rtow::color blend(double p_value, const rtow::color &p_color_0,
                           const color &p_color_1) {
    return rtow::color(
        (1.0 - p_value) * p_color_0.r() + p_value * p_color_1.r(),
        (1.0 - p_value) * p_color_0.g() + p_value * p_color_1.g(),
        (1.0 - p_value) * p_color_0.b() + p_value * p_color_1.b());
  }

  rtow::color &operator+=(const rtow::color &p_color) {
    m_r += p_color.m_r;
    m_g += p_color.m_g;
    m_b += p_color.m_b;

    return *this;
  }
};
} // namespace rtow

inline rtow::color operator+(const rtow::color &p_color_0,
                             const rtow::color &p_color_1) {
  return rtow::color(p_color_0.r() + p_color_1.r(),  //
                     p_color_0.g() + p_color_1.g(),  //
                     p_color_0.b() + p_color_1.b()); //
}

inline rtow::color operator*(const rtow::color &p_color_0,
                             const rtow::color &p_color_1) {
  return rtow::color(p_color_0.r() * p_color_1.r(),  //
                     p_color_0.g() * p_color_1.g(),  //
                     p_color_0.b() * p_color_1.b()); //
}

inline rtow::color operator*(const rtow::color &p_color, double p_value) {
  return rtow::color(p_color.r() * p_value,  //
                     p_color.g() * p_value,  //
                     p_color.b() * p_value); //
}

inline rtow::color operator*(double p_value, const rtow::color &p_color) {
  return rtow::color(p_value * p_color.r(),  //
                     p_value * p_color.g(),  //
                     p_value * p_color.b()); //
}

inline rtow::color operator/(const rtow::color &p_color, double p_value) {
  return rtow::color(p_color.r() / p_value,  //
                     p_color.g() / p_value,  //
                     p_color.b() / p_value); //
}
