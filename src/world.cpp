#include "world.h"

#include <vector>

World::World(std::vector<Sphere> objects, std::vector<Light> lights)
    : objects(objects), lights(lights) {}
