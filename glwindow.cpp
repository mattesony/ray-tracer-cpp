#include "glwindow.h"
#include "Vector.h"
#include "canvas.h"
#include "ui_glwindow.h"
#include <Eigen/Eigen>

using namespace Eigen;

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    ui->groupBoxTransformations->setEnabled(false);
    this->canvas = new Canvas(PPM_WIDTH, PPM_HEIGHT);

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

        this->glWidget->pointA = Polyhedron::ProjectPoint("AxoXY", pointA);
        this->glWidget->pointB = Polyhedron::ProjectPoint("AxoXY", pointB);
        this->glWidget->drawRotAxis = true;
        Repaint();
    });
    QObject::connect(ui->buttonSavePPM, &QPushButton::clicked, [=]()
    {
        this->canvas->writeFile(ui->lineEditPPMName->text().toUtf8().constData());
    });

    Repaint();
}

void GLWindow::Repaint()
{
    Point position = {0, 0.5, 0};
    Vector velocity = Vector({.01, .01, 0});
    Vector env = Vector({-0.0001, -0.00025, 0});
    for(int tick = 0; tick < PPM_WIDTH; tick++)
    {
        this->canvas->writePixel(floor(position.x*PPM_WIDTH), floor(position.y*PPM_HEIGHT), Vector3f(1,0,0));
        position = position + velocity;
        velocity = velocity + env;
    }
    this->canvas->writePixel(PPM_WIDTH-1, PPM_HEIGHT-1, Vector3f(0,1,0));
    this->canvas->writePixel(0, PPM_HEIGHT-1, Vector3f(1,0,0));
    this->canvas->writePixel(PPM_WIDTH-1, 0, Vector3f(0,1,1));
    this->canvas->writePixel(0, 0, Vector3f(1,1,1));
    image.loadFromData(this->canvas->getPPM().c_str());
    ui->imageOutput->setPixmap(image);
}

GLWindow::~GLWindow()
{
    delete ui;
}
