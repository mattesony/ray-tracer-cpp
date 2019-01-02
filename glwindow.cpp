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

    this->glWidget = ui->openGLWidget;

    QObject::connect(ui->buttonLoad, &QPushButton::clicked, [=]()
    {
        if(!(this->glWidget->OpenData((ui->lineEditFilename->text()).toUtf8().constData(),
                                       (ui->lineEditMatFile->text()).toUtf8().constData(),
                                       (ui->lineEditLightFile->text()).toUtf8().constData())))
            QMessageBox::information(this, "Error", "Failed to load file, check your path." );
        ui->spinObjectID->setMaximum(this->glWidget->polyhedrons.size() - 1 * (this->glWidget->polyhedrons.size() > 0));
        if(this->glWidget->polyhedrons.size() > 0)
        {
            ui->groupBoxTransformations->setEnabled(true);
            ui->buttonSave->setEnabled(true);
        }
        else
            ui->groupBoxTransformations->setEnabled(false);
        Repaint();
    });
    QObject::connect(ui->buttonSave, &QPushButton::clicked, [=]()
    {
        this->glWidget->SaveData((ui->lineEditFilename->text()).toUtf8().constData());
    });
    QObject::connect(ui->checkClipping, &QPushButton::clicked, [=](bool checked)
    {
        this->glWidget->clipping = (checked) ? true : false;
        Repaint();
    });
    QObject::connect(ui->buttonTransl, &QPushButton::clicked, [=]()
    {
        this->glWidget->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        Repaint();
    });
    QObject::connect(ui->buttonScale, &QPushButton::clicked, [=]()
    {
        this->glWidget->polyhedrons[ui->spinObjectID->value()].CentroidScale(ui->spinScaleA->value(), ui->spinScaleB->value(), ui->spinScaleG->value());
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
        this->glWidget->polyhedrons[ui->spinObjectID->value()].RotateAroundAxis(ui->spinRotA->value(), pointA, pointB);

        ui->openGLWidget->pointA = Polyhedron::ProjectPoint("AxoXY", pointA);
        ui->openGLWidget->pointB = Polyhedron::ProjectPoint("AxoXY", pointB);
        ui->openGLWidget->drawRotAxis = true;
        Repaint();
    });
}

void GLWindow::Repaint()
{
    this->glWidget->repaint();
}

GLWindow::~GLWindow()
{
    delete ui;
}
