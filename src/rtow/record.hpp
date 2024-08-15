#pragma once

#include <memory>

#include "utilities.hpp"
#include "vector.hpp"

namespace rtow {
class material;

struct record {
  rtow::vector position;
  rtow::vector normal;

  double distance = rtow::utilities::infinity;

  std::shared_ptr<rtow::material> material;
};
} // namespace rtow