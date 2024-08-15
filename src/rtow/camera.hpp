#pragma once

#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../stb/stb_image_write.h"

#include "objects/scene.hpp"

#include "color.hpp"
#include "pixel.hpp"
#include "utilities.hpp"
#include "vector.hpp"

namespace rtow {
class camera {
private:
  const rtow::vector m_position;

  const double m_aspect_ratio = 16.0 / 9.0;
  const double m_focal_length = 1.0;

  std::size_t m_image_height = 720;
  std::size_t m_image_width;

  std::vector<rtow::pixel> m_image;

  double m_viewport_height = 2.0;
  double m_viewport_width;

  rtow::vector m_viewport_vertical;
  rtow::vector m_viewport_horizontal;
  rtow::vector m_viewport_origin;

  rtow::vector m_fragment_vertical;
  rtow::vector m_fragment_horizontal;
  rtow::vector m_fragment_origin;

  const std::size_t m_sample_per_pixel = 8;

  const std::size_t m_maximum_depth = 8;

  rtow::color compute_color(const rtow::objects::scene &p_scene,
                            const rtow::ray &p_ray, double p_depth) {
    if (p_depth <= 0)
      return rtow::color(0.0, 0.0, 0.0);

    if (const auto record = p_scene.hit(p_ray, rtow::utilities::universe)) {
      rtow::color attenuation;

      if (const auto scattered =
              record->material->scatter(p_ray, record.value(), attenuation)) {
        return attenuation *
               compute_color(p_scene, scattered.value(), p_depth - 1);
      }

      return rtow::color(0.0, 0.0, 0.0);
    }

    return rtow::color::blend(0.5 * (p_ray.direction().y() + 1.0),
                              rtow::color(1.0, 1.0, 1.0),
                              rtow::color(0.5, 0.7, 1.0));
  }

public:
  camera(const rtow::vector &p_position) : m_position(p_position) {
    m_image_width = m_image_height * m_aspect_ratio;

    m_image = std::vector<rtow::pixel>(m_image_width * m_image_height);

    m_viewport_width = m_viewport_height * m_aspect_ratio;

    m_viewport_vertical = rtow::vector(0.0, -m_viewport_height, 0.0);
    m_viewport_horizontal = rtow::vector(m_viewport_width, 0.0, 0.0);
    m_viewport_origin = m_position - rtow::vector(0.0, 0.0, m_focal_length) -
                        0.5 * (m_viewport_vertical + m_viewport_horizontal);

    m_fragment_vertical = m_viewport_vertical / m_image_height;
    m_fragment_horizontal = m_viewport_horizontal / m_image_width;
    m_fragment_origin =
        m_viewport_origin + 0.5 * (m_fragment_vertical + m_fragment_horizontal);
  }

  void render(const rtow::objects::scene &p_scene) {
    m_image.clear();

    for (auto y = 0; y < m_image_height; ++y) {
      std::clog << '\r' << y + 1 << std::flush;

      for (auto x = 0; x < m_image_width; ++x) {
        rtow::color color;

        for (auto sample = 0; sample < m_sample_per_pixel; ++sample) {
          const auto vertical = m_fragment_vertical *
                                (y + rtow::utilities::random_double() - 0.5);
          const auto horizontal = m_fragment_horizontal *
                                  (x + rtow::utilities::random_double() - 0.5);

          const auto destination = m_fragment_origin + vertical + horizontal;

          color += compute_color(
              p_scene, rtow::ray(m_position, destination - m_position),
              m_maximum_depth);
        }

        m_image.push_back((color / m_sample_per_pixel).to_pixel());
      }
    }

    std::clog << std::endl;
  }

  void write_ppm() {
    std::cout << "P3\n" << m_image_width << ' ' << m_image_height << "\n255\n";

    for (auto y = 0; y < m_image_height; ++y) {
      std::clog << '\r' << y + 1 << std::flush;

      for (auto x = 0; x < m_image_width; ++x) {
        std::cout << m_image[y * m_image_width + x];
      }
    }

    std::clog << '\n';
  }

  void write_png(const char *p_file_name) {
    stbi_write_png(p_file_name, m_image_width, m_image_height, 3,
                   m_image.data(), m_image_width * 3);
  }
};
} // namespace rtow