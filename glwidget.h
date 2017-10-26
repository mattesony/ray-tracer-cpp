#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Polyhedron.h"

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
    void teardownGL();
    void setProjection(std::string proj)
    {
        this->projection = proj;
    }

    std::vector<Polyhedron> polyhedrons;

private:
     // Private Helpers
    void printContextInformation();
    std::string projection = "XY";

};
