#include "Polyhedron.h"
#include<iostream>
#include <Eigen/Eigen>

using namespace Eigen;

Polyhedron::Polyhedron(vector<Point> points, vector<Edge> edges)
{
    this->points = points;
    this->edges = edges;
}

Point Polyhedron::GetCentroid()
{
    Point centroid = {0, 0, 0};
    for(Point point : this->points)
    {
        centroid.x += point.x;
        centroid.y += point.y;
        centroid.z += point.z;
    }
    centroid.x = centroid.x / this->points.size();
    centroid.y = centroid.y / this->points.size();
    centroid.z = centroid.z / this->points.size();
    return centroid;
}

void Polyhedron::Translate(float x, float y, float z)
{
    for(Point &point : this->points)
    {
        point.x += x;
        point.y += y;
        point.z += z;
    }
    Matrix4f Mtransl;
    Mtransl << 1, 0, 0, x,
         0, 1, 0, y,
         0, 0, 1, z,
         0, 0, 0, 1;
    std::cout << Mtransl << std::endl;
}

void Polyhedron::Rotate(float alpha)
{
    alpha *= (M_PI / 180);
    for(Point &point : this->points)
    {
        float newX = cos(alpha) * point.x - sin(alpha) * point.y;
        float newY = sin(alpha) * point.x + cos(alpha) * point.y;
        point.x = newX;
        point.y = newY;
    }
}

void Polyhedron::Scale(float alpha, float beta)
{
    for(Point &point : this->points)
    {
        point.x *= alpha;
        point.y *= beta;
    }
}

void Polyhedron::CentroidRotate(float alpha)
{
    Point centroid = GetCentroid();
    Translate(-centroid.x, -centroid.y, -centroid.z);
    Rotate(alpha);
    Translate(centroid.x, centroid.y, centroid.z);
}

void Polyhedron::CentroidScale(float alpha, float beta)
{
    Point centroid = GetCentroid();
    Translate(-centroid.x, -centroid.y, -centroid.z);
    Scale(alpha, beta);
    Translate(centroid.x, centroid.y, centroid.z);
}

Polyhedron::~Polyhedron()
{
    //dtor
}
