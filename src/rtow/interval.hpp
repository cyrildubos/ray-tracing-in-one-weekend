#pragma once

#include <limits>

namespace rtow {
class interval {
private:
  double m_minimum;
  double m_maximum;

public:
  interval(double p_minimum, double p_maximum)
      : m_minimum(p_minimum), m_maximum(p_maximum) {}

  double minimum() const { return m_minimum; }
  double maximum() const { return m_maximum; }

  bool bounded(double p_value) const {
    return m_minimum < p_value && p_value < m_maximum;
  }

  bool unbounded(double p_value) const {
    return m_minimum <= p_value && p_value <= m_maximum;
  }

  double clamp(double p_value) const {
    if (p_value < m_minimum)
      return m_minimum;

    if (m_maximum < p_value)
      return m_maximum;

    return p_value;
  }
};
} // namespace rtow