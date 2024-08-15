#pragma once

#include <optional>

#include "color.hpp"
#include "ray.hpp"
#include "record.hpp"

namespace rtow {
class record;

class material {
public:
  virtual std::optional<rtow::ray>
  scatter(const rtow::ray &p_ray, const rtow::record &p_record,
          rtow::color &p_attenuation) const = 0;
};
} // namespace rtow