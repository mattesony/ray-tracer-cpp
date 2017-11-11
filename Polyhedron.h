#ifndef POLYHEDRON_H
#define POLYHEDRON_H


#include "Point.h"
#include "Edge.h"
#include <vector>
#include <string>
#include <cmath>
#include <Eigen/Eigen>

using namespace Eigen;
using namespace std;

class Polyhedron
{
    public:
        Polyhedron(vector<Point> points, vector<Edge> edges, int material);
        virtual ~Polyhedron();
        vector<Point> GetPoints()
        {
            return this->points;
        }
        vector<Edge> GetEdges()
        {
            return this->edges;
        }
        int GetMaterial()
        {
            return this->material;
        }
        Point GetCentroid();
        vector<Point> GetProjectedPoints(std::string projection);
        static Vector3f ProjectPoint(std::string projection, Vector3f point);
        void Transform(Matrix4f Mtransform);
        void Translate(float x, float y, float z);
        void RotateAroundAxis(float alpha, Vector3f pointA, Vector3f pointB);
        void Scale(float alpha, float beta, float gamma);
        void CentroidScale(float alpha, float beta, float gamma);

    private:
        vector<Point> points;
        vector<Edge> edges;
        int material;
};

#endif // POLYHEDRON_H
