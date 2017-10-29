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
        ui->openGLWidget->OpenData((ui->lineEditFilename->text()).toUtf8().constData());
        ui->spinObjectID->setMaximum(ui->openGLWidget->polyhedrons.size() - 1);
        if(ui->openGLWidget->polyhedrons.size() > 0)
        {
            ui->groupBoxTransformations->setEnabled(true);
            ui->buttonSave->setEnabled(true);
        }
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonSave, &QPushButton::clicked, [=]()
    {
        ui->openGLWidget->SaveData((ui->lineEditFilename->text()).toUtf8().constData());
    });
    QObject::connect(ui->buttonXYProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("AxoXY");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonXZProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("AxoXZ");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonYZProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("AxoYZ");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->checkClipping, &QPushButton::clicked, [=](bool checked)
    {
        ui->openGLWidget->clipping = (checked) ? true : false;
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->checkIndices1, &QPushButton::clicked, [=](bool checked)
    {
        ui->openGLWidget->indicesStartAt1 = (checked) ? true : false;
    });
    QObject::connect(ui->buttonTransl, &QPushButton::clicked, [=]()
    {
        ui->openGLWidget->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonScale, &QPushButton::clicked, [=]()
    {
        ui->openGLWidget->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
        ui->openGLWidget->repaint();
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
        ui->openGLWidget->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);
        if (ui->buttonXYProj->isChecked())
        {
            ui->openGLWidget->pointA = Polyhedron::ProjectPoint("AxoXY", pointA);
            ui->openGLWidget->pointB = Polyhedron::ProjectPoint("AxoXY", pointB);
        }
        else if(ui->buttonXZProj->isChecked())
        {
            ui->openGLWidget->pointA = Polyhedron::ProjectPoint("AxoXZ", pointA);
            ui->openGLWidget->pointB = Polyhedron::ProjectPoint("AxoXZ", pointB);
        }
        else if(ui->buttonYZProj->isChecked())
        {
            ui->openGLWidget->pointA = Polyhedron::ProjectPoint("AxoYZ", pointA);
            ui->openGLWidget->pointB = Polyhedron::ProjectPoint("AxoYZ", pointB);
        }
        ui->openGLWidget->drawRotAxis = true;
        ui->openGLWidget->repaint();
    });
}

GLWindow::~GLWindow()
{
    delete ui;
}
