#pragma once

#include <memory>

#include "../object.hpp"
#include "../vector.hpp"

namespace rtow::objects {
class sphere : public rtow::object {
private:
  const rtow::vector m_center;

  const double m_radius;

  const std::shared_ptr<rtow::material> m_material;

public:
  sphere(const rtow::vector &p_center, double p_radius,
         const std::shared_ptr<rtow::material> p_material)
      : m_center(p_center), m_radius(p_radius), m_material(p_material) {}

  const rtow::vector &center() const { return m_center; }

  const double radius() const { return m_radius; };

  const std::shared_ptr<rtow::material> &material() const {
    return m_material;
  }

  std::optional<rtow::record>
  hit(const rtow::ray &p_ray,
      const rtow::interval &p_interval) const override {
    const auto vector = p_ray.origin() - m_center;

    const auto a = p_ray.direction().squared_norm();
    const auto h = rtow::vector::dot(vector, p_ray.direction());
    const auto c = vector.squared_norm() - m_radius * m_radius;

    const auto d = h * h - a * c;

    if (d < 0.0) {
      return std::nullopt;
    }

    const auto sqrt_d = std::sqrt(d);

    auto root = (-h - sqrt_d) / a;

    if (!p_interval.bounded(root)) {
      root = (-h + sqrt_d) / a;

      if (!p_interval.bounded(root))
        return std::nullopt;
    }

    const auto normal = (p_ray.at(root) - m_center).normalize();

    return std::optional<rtow::record>({.position = p_ray.at(root),
                                         .normal = p_ray.normal(normal),
                                         .distance = root,
                                         .material = m_material});
  }
};
} // namespace rtow::objects