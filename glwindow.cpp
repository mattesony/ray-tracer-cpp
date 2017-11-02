#include "glwindow.h"
#include "ui_glwindow.h"
#include <Eigen/Eigen>

using namespace Eigen;

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    ui->groupBoxTransformations->setEnabled(false);

    QObject::connect(ui->buttonLoad, &QPushButton::clicked, [=]()
    {
        ui->openGLWidgetXY->setProjection("AxoXY");
        ui->openGLWidgetXZ->setProjection("AxoXZ");
        ui->openGLWidgetYZ->setProjection("AxoYZ");
        ui->openGLWidgetXY->OpenData((ui->lineEditFilename->text()).toUtf8().constData());
        ui->openGLWidgetXZ->OpenData((ui->lineEditFilename->text()).toUtf8().constData());
        ui->openGLWidgetYZ->OpenData((ui->lineEditFilename->text()).toUtf8().constData());
        ui->spinObjectID->setMaximum(ui->openGLWidgetXY->polyhedrons.size() - 1);
        if(ui->openGLWidgetXY->polyhedrons.size() > 0)
        {
            ui->groupBoxTransformations->setEnabled(true);
            ui->buttonSave->setEnabled(true);
        }
        Repaint();
    });
    QObject::connect(ui->buttonSave, &QPushButton::clicked, [=]()
    {
        ui->openGLWidgetXY->SaveData((ui->lineEditFilename->text()).toUtf8().constData());
    });
    QObject::connect(ui->checkClipping, &QPushButton::clicked, [=](bool checked)
    {
        ui->openGLWidgetXY->clipping = (checked) ? true : false;
        ui->openGLWidgetXZ->clipping = (checked) ? true : false;
        ui->openGLWidgetYZ->clipping = (checked) ? true : false;
        Repaint();
    });
    QObject::connect(ui->checkIndices1, &QPushButton::clicked, [=](bool checked)
    {
        ui->openGLWidgetXY->indicesStartAt1 = (checked) ? true : false;
        ui->openGLWidgetXZ->indicesStartAt1 = (checked) ? true : false;
        ui->openGLWidgetYZ->indicesStartAt1 = (checked) ? true : false;
        Repaint();
    });
    QObject::connect(ui->buttonTransl, &QPushButton::clicked, [=]()
    {
        ui->openGLWidgetXY->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        ui->openGLWidgetXZ->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        ui->openGLWidgetYZ->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        Repaint();
    });
    QObject::connect(ui->buttonScale, &QPushButton::clicked, [=]()
    {
        ui->openGLWidgetXY->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
        ui->openGLWidgetXZ->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
        ui->openGLWidgetYZ->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
        Repaint();
    });
    QObject::connect(ui->buttonRot, &QPushButton::clicked, [=]()
    {
        Vector3f pointA;
        Vector3f pointB;
        float x, y, z;
        if(std::stringstream(ui->lineRotPa->text().toStdString()) >> x >> y >> z)
            pointA = {x, y, z};
        else
            std::cout << "Failed to read point " << ui->lineRotPa->text().toStdString() << ": must be formatted like \"0.32 0.0 0.45\"" << std::endl;
        if(std::stringstream(ui->lineRotPb->text().toStdString()) >> x >> y >> z)
            pointB = {x, y, z};
        else
            std::cout << "Failed to read point " << ui->lineRotPb->text().toStdString() << ": must be formatted like \"0.32 0.0 0.45\"" << std::endl;
        ui->openGLWidgetXY->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);
        ui->openGLWidgetXZ->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);
        ui->openGLWidgetYZ->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);

        ui->openGLWidgetXY->pointA = Polyhedron::ProjectPoint("AxoXY", pointA);
        ui->openGLWidgetXY->pointB = Polyhedron::ProjectPoint("AxoXY", pointB);
        ui->openGLWidgetXY->drawRotAxis = true;

        ui->openGLWidgetXZ->pointA = Polyhedron::ProjectPoint("AxoXZ", pointA);
        ui->openGLWidgetXZ->pointB = Polyhedron::ProjectPoint("AxoXZ", pointB);
        ui->openGLWidgetXZ->drawRotAxis = true;

        ui->openGLWidgetYZ->pointA = Polyhedron::ProjectPoint("AxoYZ", pointA);
        ui->openGLWidgetYZ->pointB = Polyhedron::ProjectPoint("AxoYZ", pointB);
        ui->openGLWidgetYZ->drawRotAxis = true;

        Repaint();
    });
}

void GLWindow::Repaint()
{
    ui->openGLWidgetXY->repaint();
    ui->openGLWidgetXZ->repaint();
    ui->openGLWidgetYZ->repaint();
}

GLWindow::~GLWindow()
{
    delete ui;
}
