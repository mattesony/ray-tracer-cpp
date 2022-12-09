#ifndef CANVAS_H_
#define CANVAS_H_

#include <Eigen/Eigen>
#include <string>
#include <vector>

using Eigen::Vector3f;
class Canvas {
 public:
  Canvas(int width, int height);
  bool writePixel(int x, int y, Vector3f color);
  std::string getPPM();
  void writeFile(std::string name = "test.ppm");

 private:
  int width, height, size;
  std::vector<Vector3f> pixelArray;
};

#endif  // CANVAS_H_
