#pragma once

#include <cmath>
#include <iostream>

#include "utilities.hpp"

namespace rtow {
class vector {
private:
  double m_x = 0.0;
  double m_y = 0.0;
  double m_z = 0.0;

public:
  vector() {}

  vector(double p_x, double p_y, double p_z) : m_x(p_x), m_y(p_y), m_z(p_z) {}

  double x() const { return m_x; }
  double y() const { return m_y; }
  double z() const { return m_z; }

  bool near_zero() const {
    return m_x < rtow::utilities::epsilon && //
           m_y < rtow::utilities::epsilon && //
           m_z < rtow::utilities::epsilon;   //
  }

  double squared_norm() const { return m_x * m_x + m_y * m_y + m_z * m_z; }

  double norm() const { return std::sqrt(squared_norm()); }

  rtow::vector normalize() const {
    return rtow::vector(m_x / norm(), m_y / norm(), m_z / norm());
  }

  static rtow::vector random() {
    return rtow::vector(rtow::utilities::random_double(),  //
                        rtow::utilities::random_double(),  //
                        rtow::utilities::random_double()); //
  }

  static rtow::vector random(double m_minimum, double m_maximum) {
    return rtow::vector(rtow::utilities::random_double(m_minimum, m_maximum),
                        rtow::utilities::random_double(m_minimum, m_maximum),
                        rtow::utilities::random_double(m_minimum, m_maximum));
  }

  static rtow::vector random_in_sphere() {
    while (true) {
      const auto vector = random(-1.0, 1.0);

      if (vector.squared_norm() < 1.0)
        return vector;
    }
  }

  static rtow::vector random_in_hemisphere(const rtow::vector &m_normal) {
    const auto vector = random_in_sphere();

    return dot(vector, m_normal) > 0.0 ? vector : -vector;
  }

  static double dot(const rtow::vector &p_vector_0,
                    const rtow::vector &p_vector_1) {
    return p_vector_0.m_x * p_vector_1.m_x + //
           p_vector_0.m_y * p_vector_1.m_y + //
           p_vector_0.m_z * p_vector_1.m_z;  //
  }

  rtow::vector operator+() const { return rtow::vector(+m_x, +m_y, +m_z); }

  rtow::vector operator-() const { return rtow::vector(-m_x, -m_y, -m_z); }

  rtow::vector &operator+=(const rtow::vector &p_vector) {
    m_x += p_vector.m_x;
    m_y += p_vector.m_y;
    m_z += p_vector.m_z;

    return *this;
  }

  rtow::vector &operator-=(const rtow::vector &p_vector) {
    m_x -= p_vector.m_x;
    m_y -= p_vector.m_y;
    m_z -= p_vector.m_z;

    return *this;
  }

  rtow::vector &operator*=(double p_value) {
    m_x *= p_value;
    m_y *= p_value;
    m_z *= p_value;

    return *this;
  }

  rtow::vector &operator/=(double p_value) {
    m_x /= p_value;
    m_y /= p_value;
    m_z /= p_value;

    return *this;
  }
};
} // namespace rtow

inline std::ostream &operator<<(std::ostream &p_ostream,
                                const rtow::vector &p_vector) {
  return p_ostream << p_vector.x() << ' '   //
                   << p_vector.y() << ' '   //
                   << p_vector.z() << '\n'; //
}

inline rtow::vector operator+(const rtow::vector &p_vector_0,
                              const rtow::vector &p_vector_1) {
  return rtow::vector(p_vector_0.x() + p_vector_1.x(),
                      p_vector_0.y() + p_vector_1.y(),
                      p_vector_0.z() + p_vector_1.z());
}

// inline vector operator+(const vector &p_vector, double p_value) {
//   return vector(p_vector.x() + p_value,  //
//                 p_vector.y() + p_value,  //
//                 p_vector.z() + p_value); //
// }

// inline vector operator+(double p_value, const vector &p_vector) {
//   return vector(p_value + p_vector.x(),  //
//                 p_value + p_vector.y(),  //
//                 p_value + p_vector.z()); //
// }

inline rtow::vector operator-(const rtow::vector &p_vector_0,
                              const rtow::vector &p_vector_1) {
  return rtow::vector(p_vector_0.x() - p_vector_1.x(),
                      p_vector_0.y() - p_vector_1.y(),
                      p_vector_0.z() - p_vector_1.z());
}

// inline vector operator*(const vector &p_vector_0, const vector &p_vector_1) {
//   return vector(p_vector_0.x() * p_vector_1.x(),
//                 p_vector_0.y() * p_vector_1.y(),
//                 p_vector_0.z() * p_vector_1.z());
// }

inline rtow::vector operator*(const rtow::vector &p_vector, double p_value) {
  return rtow::vector(p_vector.x() * p_value,  //
                      p_vector.y() * p_value,  //
                      p_vector.z() * p_value); //
}

inline rtow::vector operator*(double p_value, const rtow::vector &p_vector) {
  return rtow::vector(p_value * p_vector.x(),  //
                      p_value * p_vector.y(),  //
                      p_value * p_vector.z()); //
}

inline rtow::vector operator/(const rtow::vector &p_vector, double p_value) {
  return rtow::vector(p_vector.x() / p_value,  //
                      p_vector.y() / p_value,  //
                      p_vector.z() / p_value); //
}