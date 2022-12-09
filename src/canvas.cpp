#include "./canvas.h"

#include <fstream>
#include <sstream>

int MAX_COLOR_VALUE = 255;

Canvas::Canvas(int width, int height) {
  this->width = width;
  this->height = height;
  this->size = this->width * this->height;
  this->pixelArray.reserve(this->size);

  Vector3f black = {0, 0, 0};
  for (int i = 0; i < this->size; i++) {
    this->pixelArray.push_back(black);
  }
}
bool Canvas::writePixel(int x, int y, Vector3f color) {
  if ((0 <= x && x < this->width) && (0 <= y && y < this->height)) {
    this->pixelArray[(this->height - 1 - y) * this->width + x] = color;
    return true;
  }
  // TODO: log here
  return false;
}

int floorAndClamp(int val) {
  // TODO: Add logging here to make clamping obvious
  if (0 > val) {
    return 0;
  } else if (MAX_COLOR_VALUE < val) {
    return MAX_COLOR_VALUE;
  } else {
    // round down to integer
    return floor(val);
  }
}

std::string Canvas::getPPM() {
  std::stringstream output;
  // identifier
  output << "P3" << std::endl;
  // width height
  output << this->width << " " << this->height << std::endl;
  // max color value
  output << MAX_COLOR_VALUE << std::endl;
  for (int row = 0; row < this->height; row++) {
    int lineLen = 0;
    for (int column = 0; column < this->width; column++) {
      Vector3f pixel = this->pixelArray[row * this->width + column];
      for (int colorIndex = 0; colorIndex < 3; colorIndex++) {
        std::string intStr =
            std::to_string(floorAndClamp(pixel(colorIndex) * MAX_COLOR_VALUE));
        if (70 < lineLen + static_cast<int>(0 != lineLen) + intStr.length()) {
          output << std::endl;
          lineLen = 0;
        }
        lineLen += static_cast<int>(0 != lineLen) + intStr.length();
        if (0 != lineLen) output << " ";
        output << intStr;
      }
    }
    output << std::endl;
  }
  return output.str();
}

void Canvas::writeFile(std::string name) {
  std::ofstream file;

  file.open(name);
  file << this->getPPM();
  file.close();
}
