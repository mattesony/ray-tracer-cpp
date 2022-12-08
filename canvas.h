#ifndef CANVAS_H
#define CANVAS_H


#include <Eigen/Eigen>
#include <array>

using namespace Eigen;

class Canvas
{
public:
    Canvas(int width, int height);
    bool writePixel(int x, int y, Vector3f color);
    std::string getPPM();
    void writeFile(std::string name="test.ppm");
private:
    int width, height, size;
    std::vector<Vector3f> pixelArray;
};

#endif // CANVAS_H
