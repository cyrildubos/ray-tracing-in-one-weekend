#pragma once

#include <iostream>

namespace rtow {
struct pixel {
  std::uint8_t r;
  std::uint8_t g;
  std::uint8_t b;
};
} // namespace rtow

inline std::ostream &operator<<(std::ostream &p_ostream,
                                const rtow::pixel &p_pixel) {
  return p_ostream << static_cast<int>(p_pixel.r) << ' '   //
                   << static_cast<int>(p_pixel.g) << ' '   //
                   << static_cast<int>(p_pixel.b) << '\n'; //
}