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

void Polyhedron::Transform(Matrix4f Mtransform)
{
    for(Point &point : this->points)
    {
        Vector4f p = {point.x, point.y, point.z, 1};
        VectorXf pBar = Mtransform * p;
        point.x = pBar(0);
        point.y = pBar(1);
        point.z = pBar(2);
    }
}

void Polyhedron::Translate(float x, float y, float z)
{
    Matrix4f Mtransl;
    Mtransl << 1, 0, 0, x,
         0, 1, 0, y,
         0, 0, 1, z,
         0, 0, 0, 1;
    Transform(Mtransl);
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

void Polyhedron::Scale(float alpha, float beta, float gamma)
{
    Vector4f scale = {alpha, beta, gamma, 1};
    Matrix4f Mscale = scale.asDiagonal();
    Transform(Mscale);
    std::cout << this->points[0].x << this->points[0].y << this->points[0].z << std::endl;
    std::cout << this->points[1].x << this->points[1].y << this->points[1].z << std::endl;
    std::cout << this->points[2].x << this->points[2].y << this->points[2].z << std::endl;
    std::cout << this->points[3].x << this->points[3].y << this->points[3].z << std::endl;
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
    //Scale(alpha, beta);
    Translate(centroid.x, centroid.y, centroid.z);
}

Polyhedron::~Polyhedron()
{
    //dtor
}
