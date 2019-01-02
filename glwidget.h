#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Polyhedron.h"
#include "light.h"
#include "material.h"
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

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    int width;
    int height;
    Vector3f linInt(Vector3f colorA, Vector3f colorB, float t);
    bool OpenData(std::string filename, std::string matfilename, std::string lightfilename);
    bool SaveData(std::string filename);
    void Megapixel(float x, float y, Vector3f color);
    void DrawPixel(float x, float y, Vector3f color);
    void DrawBresenham(Vector2f pointA, Vector2f pointB, Vector3f colorA, Vector3f colorB);
    void drawLine(Vector3f pointA, Vector3f pointB);
    void teardownGL();
    void setProjection(std::string proj)
    {
        this->projection = proj;
    }
    void setPolyhedrons(std::vector<Polyhedron> polyhedrons)
    {
        this->polyhedrons = polyhedrons;
    }

    void setMaterials(std::vector<Material> materials)
    {
        this->materials = materials;
    }
    void setLight(Light light)
    {
        this->light = light;
    }


    std::vector<Polyhedron> polyhedrons;
    std::vector<Material> materials;
    Light light;

    Vector3f pointA;
    Vector3f pointB;
    bool drawRotAxis = false;
    bool clipping = false;

private:
     // Private Helpers
    void printContextInformation();
    std::string projection = "AxoXY";

};
