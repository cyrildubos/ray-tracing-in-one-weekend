#pragma once

#include "../material.hpp"

namespace rtow::materials {
class normal : public rtow::material {
public:
  std::optional<rtow::ray>
  scatter(const rtow::ray &p_ray, const rtow::record &p_record,
          rtow::color &p_attenuation) const override {
    p_attenuation = 0.5 * rtow::color(p_record.normal.x() + 1.0,  //
                                       p_record.normal.y() + 1.0,  //
                                       p_record.normal.z() + 1.0); //

    auto direction = p_record.normal + rtow::vector::random_in_sphere();

    if (direction.near_zero()) {
      direction = p_record.normal;
    }

    return rtow::ray(p_record.position, direction);
  };
};
} // namespace rtow::materials