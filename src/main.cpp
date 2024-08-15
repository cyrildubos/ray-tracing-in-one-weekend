#include "rtow/rtow.hpp"

int main() {
  auto normal = std::make_shared<rtow::materials::normal>();

  rtow::objects::scene scene;

  scene.add(std::make_shared<rtow::objects::sphere>(
      rtow::vector(0.0, -100.5, -1.0), 100.0, normal));
  scene.add(std::make_shared<rtow::objects::sphere>(
      rtow::vector(0.0, 0.0, -1.0), 0.5, normal));

  rtow::camera camera(rtow::vector(0.0, 0.0, 0.0));

  camera.render(scene);

  camera.write_png("image.png");

  return EXIT_SUCCESS;
}