#include "Polyhedron.h"
#include<iostream>
#include <Eigen/Eigen>

using namespace Eigen;

Polyhedron::Polyhedron(vector<Point> points, vector<Triangle> triangles, int material)
{
    this->points = points;
    this->triangles = triangles;
    this->material = material;
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

vector<Point> Polyhedron::GetProjectedPoints(std::string projection)
{
    Matrix4f Mprojection;
    if(projection == "AxoXY")
    {
        Mprojection << 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    else if(projection == "AxoXZ")
    {
        Mprojection << 1, 0, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    else if(projection == "AxoYZ")
    {
        Mprojection << 0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    vector<Point> projectedPoints;
    for(Point point : this->points)
    {
        Vector4f p = {point.x, point.y, point.z, 1};
        VectorXf pBar = Mprojection * p;
        projectedPoints.push_back({pBar(0), pBar(1), pBar(2)});
    }
    return projectedPoints;
}

Vector3f Polyhedron::ProjectPoint(std::string projection, Vector3f point)
{
    Matrix4f Mprojection;
    if(projection == "AxoXY")
    {
        Mprojection << 1, 0, 0, 0,
             0, 1, 0, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    else if(projection == "AxoXZ")
    {
        Mprojection << 1, 0, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    else if(projection == "AxoYZ")
    {
        Mprojection << 0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 0,
             0, 0, 0, 1;
    }
    Vector4f p;
    p << point, 1;
    Vector4f pBar = Mprojection * p;
    return {pBar(0), pBar(1), pBar(2)};
}

void Polyhedron::Transform(Matrix4f Mtransform)
{
    for(Point &point : this->points)
    {
        Vector4f p = {point.x, point.y, point.z, 1};
        Vector4f pBar = Mtransform * p;
        point = Point({pBar(0), pBar(1), pBar(2)});
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

void Polyhedron::RotateAroundAxis(float a, Vector3f pointA, Vector3f pointB)
{
    Vector3f nV = (pointB - pointA)/(pointB - pointA).norm();
    a *= (M_PI / 180);
    Matrix4f Mrot;
    Mrot << cos(a) + pow(nV(0), 2) * (1-cos(a)), nV(0) * nV(1) * (1 - cos(a)) - nV(2) * sin(a), nV(0) * nV(2) * (1 - cos(a)) + nV(1) * sin(a), 0,
         nV(1) * nV(0) * (1 - cos(a)) + nV(2) * sin(a), cos(a) + pow(nV(1), 2) * (1 - cos(a)), nV(1)*nV(2)*(1-cos(a)) - nV(0) * sin(a), 0,
         nV(2) * nV(0) * (1 - cos(a)) - nV(1) * sin(a), nV(2)*nV(1)*(1-cos(a)) + nV(0) * sin(a), cos(a) + pow(nV(2), 2) * (1-cos(a)), 0,
         0, 0, 0, 1;

    Translate(-pointA(0), -pointA(1), -pointA(2));
    Transform(Mrot);
    Translate(pointA(0), pointA(1), pointA(2));
    std::cout << nV << std::endl << std::endl << Mrot << std::endl << std::endl;
}

void Polyhedron::Scale(float alpha, float beta, float gamma)
{
    Vector4f scale = {alpha, beta, gamma, 1};
    Matrix4f Mscale = scale.asDiagonal();
    Transform(Mscale);
}

void Polyhedron::CentroidScale(float alpha, float beta, float gamma)
{
    Point centroid = GetCentroid();
    Translate(-centroid.x, -centroid.y, -centroid.z);
    Scale(alpha, beta, gamma);
    Translate(centroid.x, centroid.y, centroid.z);
}

Polyhedron::~Polyhedron()
{
    //dtor
}
