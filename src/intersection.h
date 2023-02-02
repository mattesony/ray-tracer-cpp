#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <memory>

#include "sphere.h"
class Intersection {
 public:
  float t;
  std::shared_ptr<Sphere const> object;

  Intersection(float t_, std::shared_ptr<Sphere const> object_);

  bool operator==(Intersection const& rhs) const;
  bool operator<(Intersection const& rhs) const;
};

template <typename... VarArgs>
std::vector<Intersection> intersections(VarArgs const&... args) {
  std::vector<Intersection> intersections{args...};
  // TODO: Sorting data structure instead?
  sort(intersections.begin(), intersections.end());
  return intersections;
}

Intersection hit(std::vector<Intersection> intersections);

#endif  // INTERSECTION_H_
