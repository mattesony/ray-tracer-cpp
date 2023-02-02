#include "intersection.h"

Intersection::Intersection(float t_, std::shared_ptr<Sphere const> object_)
    : t(t_), object(object_) {}

bool Intersection::operator==(Intersection const& rhs) const {
  return t == rhs.t && object == rhs.object;
}

bool Intersection::operator<(Intersection const& rhs) const {
  return t < rhs.t;
}

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

std::vector<Intersection> buildIntersections(
    std::shared_ptr<Sphere const> object, std::vector<float> ts) {
  std::vector<Intersection> output;
  for (auto t : ts) {
    output.push_back(Intersection(t, object));
  }
  return output;
}
