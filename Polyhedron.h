#ifndef POLYHEDRON_H
#define POLYHEDRON_H


#include "Point.h"
#include "Edge.h"
#include <vector>
#include <cmath>
#include <Eigen/Eigen>

using namespace Eigen;
using namespace std;

class Polyhedron
{
    public:
        Polyhedron(vector<Point> points, vector<Edge> edges);
        virtual ~Polyhedron();
        vector<Point> GetPoints()
        {
            return this->points;
        }
        vector<Edge> GetEdges()
        {
            return this->edges;
        }
        Point GetCentroid();
        void Transform(Matrix4f Mtransform);
        void Translate(float x, float y, float z);
        void Rotate(float alpha);
        void Scale(float alpha, float beta, float gamma);
        void CentroidRotate(float alpha);
        void CentroidScale(float alpha, float beta);

    protected:

    private:
        vector<Point> points;
        vector<Edge> edges;
};

#endif // POLYHEDRON_H
