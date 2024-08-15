#pragma once

#include <memory>
#include <vector>

#include "../object.hpp"

namespace rtow::objects {
class scene : public rtow::object {
private:
  std::vector<std::shared_ptr<rtow::object>> m_objects;

public:
  void clear() { m_objects.clear(); }

  void add(std::shared_ptr<rtow::object> p_object) {
    m_objects.push_back(p_object);
  }

  std::optional<rtow::record>
  hit(const rtow::ray &p_ray,
      const rtow::interval &p_interval) const override {
    rtow::record record = {};

    auto maximum = p_interval.maximum();

    for (const auto &object : m_objects) {
      rtow::interval interval(p_interval.minimum(), maximum);

      if (const auto r = object->hit(p_ray, interval)) {
        record = r.value();

        maximum = r->distance;
      }
    }

    if (record.distance == rtow::utilities::infinity) {
      return std::nullopt;
    }

    return record;
  }
};
} // namespace rtow::objects