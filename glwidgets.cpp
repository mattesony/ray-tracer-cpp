#include "glwidgets.h"

GLWidgets::GLWidgets(GLWidget *openGLWidgetXY, GLWidget *openGLWidgetXZ, GLWidget *openGLWidgetYZ)
{
    this->openGLWidgetXY = openGLWidgetXY;
    this->openGLWidgetXZ = openGLWidgetXZ;
    this->openGLWidgetYZ = openGLWidgetYZ;

    this->openGLWidgetXY->setPolyhedrons(this->polyhedrons);
    this->openGLWidgetXZ->setPolyhedrons(this->polyhedrons);
    this->openGLWidgetYZ->setPolyhedrons(this->polyhedrons);

    this->openGLWidgetXY->setProjection("AxoXY");
    this->openGLWidgetXZ->setProjection("AxoXZ");
    this->openGLWidgetYZ->setProjection("AxoYZ");
}

void GLWidgets::Repaint()
{
    this->openGLWidgetXY->polyhedrons = this->polyhedrons;
    this->openGLWidgetXZ->polyhedrons = this->polyhedrons;
    this->openGLWidgetYZ->polyhedrons = this->polyhedrons;

    this->openGLWidgetXY->repaint();
    //this->openGLWidgetXZ->repaint();
    //this->openGLWidgetYZ->repaint();
}
