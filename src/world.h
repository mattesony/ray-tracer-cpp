#ifndef WORLD_H_
#define WORLD_H_

#include <vector>

#include "./light.h"
#include "./sphere.h"

class World {
 public:
  std::vector<Sphere> objects;
  std::vector<Light> lights;

  World(std::vector<Sphere> objects = {}, std::vector<Light> lights = {});
};

#endif  // WORLD_H_
