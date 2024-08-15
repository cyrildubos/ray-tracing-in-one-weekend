#pragma once

#include <optional>

#include "interval.hpp"
#include "ray.hpp"
#include "record.hpp"

namespace rtow {
class object {
public:
  virtual std::optional<rtow::record>
  hit(const rtow::ray &p_ray, const rtow::interval &p_interval) const = 0;
};
} // namespace rtow