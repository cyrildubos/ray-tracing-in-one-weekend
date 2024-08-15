#pragma once

#include <limits>
#include <random>

namespace rtow::utilities {
static const double infinity = std::numeric_limits<double>::infinity();
static const double epsilon = std::numeric_limits<double>::epsilon();

static const rtow::interval universe(epsilon, infinity);

inline double random_double() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);

  static std::mt19937 generator;

  return distribution(generator);
}

inline double random_double(double p_minimum, double p_maximum) {
  return p_minimum + (p_maximum - p_minimum) * random_double();
}

} // namespace rtow::utilities
