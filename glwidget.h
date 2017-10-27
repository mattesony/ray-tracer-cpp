#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Polyhedron.h"
#include <Eigen/Eigen>

using namespace Eigen;


class GLWidget :
        public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void OpenData(std::string filename);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void drawLine(Vector3f pointA, Vector3f pointB);
    void teardownGL();
    void setProjection(std::string proj)
    {
        this->projection = proj;
    }

    std::vector<Polyhedron> polyhedrons;
    Vector3f pointA;
    Vector3f pointB;
    bool drawRotAxis = false;

private:
     // Private Helpers
    void printContextInformation();
    std::string projection = "AxoXY";


};
