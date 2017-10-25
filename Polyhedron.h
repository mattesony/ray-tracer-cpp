#ifndef POLYHEDRON_H
#define POLYHEDRON_H


#include "Point.h"
#include "Edge.h"
#include <vector>
#include <cmath>

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
        void Translate(float x, float y, float z);
        void Rotate(float alpha);
        void Scale(float alpha, float beta);
        void CentroidRotate(float alpha);
        void CentroidScale(float alpha, float beta);

    protected:

    private:
        vector<Point> points;
        vector<Edge> edges;
};

#endif // POLYHEDRON_H
