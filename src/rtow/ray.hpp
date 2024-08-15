#pragma once

#include "vector.hpp"

namespace rtow {
class ray {
private:
  rtow::vector m_origin;
  rtow::vector m_direction;

public:
  ray(const rtow::vector &p_origin, const rtow::vector &p_direction)
      : m_origin(p_origin), m_direction(p_direction) {}

  const rtow::vector &origin() const { return m_origin; }
  const rtow::vector &direction() const { return m_direction; }

  const rtow::vector at(double p_double) const {
    return m_origin + p_double * m_direction;
  }

  const rtow::vector normal(const rtow::vector &p_normal) const {
    return rtow::vector::dot(m_direction, p_normal) < 0.0 ? +p_normal
                                                           : -p_normal;
  }
};
} // namespace rtow