#include "intersection.h"

Intersection::Intersection(float t_, std::shared_ptr<Sphere const> object_)
    : t(t_), object(object_) {}

Intersection hit(std::vector<Intersection> intersections) {
  for (auto const& intersection : intersections) {
    if (intersection.t >= 0.f) return intersection;
  }
  return {0, nullptr};
}

template <typename... Args>
std::vector<Intersection> Intersections(Args const&... args) {
  std::vector<Intersection> xs{args...};
  std::sort(xs.begin(), xs.end());
  return xs;
}

bool Intersection::operator==(Intersection const& rhs) const {
  return t == rhs.t && object == rhs.object;
}

bool Intersection::operator<(Intersection const& rhs) const {
  return t < rhs.t;
}
