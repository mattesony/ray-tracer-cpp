#ifndef GLWIDGETS_H
#define GLWIDGETS_H

#include <glwidget.h>
#include "Polyhedron.h"


class GLWidgets
{
public:
    GLWidgets(GLWidget *openGLWidgetXY, GLWidget *openGLWidgetXZ, GLWidget *openGLWidgetYZ);



    void Repaint();

    void SetClipping(bool clipping)
    {
        this->openGLWidgetXY->clipping = clipping;
        this->openGLWidgetXZ->clipping = clipping;
        this->openGLWidgetYZ->clipping = clipping;
    }

    std::vector<Polyhedron> polyhedrons;
    std::vector<Material> materials;
    Light light;

private:
    GLWidget *openGLWidgetXY;
    GLWidget *openGLWidgetXZ;
    GLWidget *openGLWidgetYZ;
};

#endif // GLWIDGETS_H
