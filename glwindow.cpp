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

    this->glWidgets =new GLWidgets(ui->openGLWidgetXY, ui->openGLWidgetXZ, ui->openGLWidgetYZ);

    QObject::connect(ui->buttonLoad, &QPushButton::clicked, [=]()
    {
        if(!(this->glWidgets->OpenData((ui->lineEditFilename->text()).toUtf8().constData()))) QMessageBox::information(this, "Error", "Failed to load file, check your path." );
        ui->spinObjectID->setMaximum(this->glWidgets->polyhedrons.size() - 1);
        if(this->glWidgets->polyhedrons.size() > 0)
        {
            ui->groupBoxTransformations->setEnabled(true);
            ui->buttonSave->setEnabled(true);
        }
        Repaint();
    });
    QObject::connect(ui->buttonSave, &QPushButton::clicked, [=]()
    {
        this->glWidgets->SaveData((ui->lineEditFilename->text()).toUtf8().constData());
    });
    QObject::connect(ui->checkClipping, &QPushButton::clicked, [=](bool checked)
    {
        this->glWidgets->SetClipping((checked) ? true : false);
        Repaint();
    });
    QObject::connect(ui->checkIndices1, &QPushButton::clicked, [=](bool checked)
    {
        this->glWidgets->indicesStartAt1 = (checked) ? true : false;
        Repaint();
    });
    QObject::connect(ui->buttonTransl, &QPushButton::clicked, [=]()
    {
        this->glWidgets->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        Repaint();
    });
    QObject::connect(ui->buttonScale, &QPushButton::clicked, [=]()
    {
        this->glWidgets->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
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
        this->glWidgets->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);

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
    this->glWidgets->Repaint();
}

GLWindow::~GLWindow()
{
    delete ui;
}
