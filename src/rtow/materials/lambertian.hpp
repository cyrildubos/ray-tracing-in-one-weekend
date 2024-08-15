#pragma once

#include "../material.hpp"

namespace rtow::materials {
class lambertian : public rtow::material {
private:
  const rtow::color m_albedo;

public:
  lambertian(const rtow::color &p_albedo) : m_albedo(p_albedo) {}

  std::optional<rtow::ray>
  scatter(const rtow::ray &p_ray, const rtow::record &p_record,
          rtow::color &p_attenuation) const override {
    p_attenuation = m_albedo;

    auto direction = p_record.normal + rtow::vector::random_in_sphere();

    if (direction.near_zero()) {
      direction = p_record.normal;
    }

    return rtow::ray(p_record.position, direction);
  };
};
} // namespace rtow::materials