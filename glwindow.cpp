#include "glwindow.h"
#include "ui_glwindow.h"

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonLoad, &QPushButton::clicked, [=]()
    {
        ui->openGLWidget->OpenData((ui->lineEditFilename->text()).toUtf8().constData());
        ui->spinObjectID->setMaximum(ui->openGLWidget->polyhedrons.size() - 1);
        if(ui->openGLWidget->polyhedrons.size() > 0)
        {
            ui->groupBoxTransformations->setEnabled(true);
            ui->buttonTransl->setEnabled(true);
        }
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonXYProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("XY");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonXZProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("XZ");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonYZProj, &QPushButton::clicked, [=](bool toggled)
    {
        if(toggled)
            ui->openGLWidget->setProjection("YZ");
        ui->openGLWidget->repaint();
    });
    QObject::connect(ui->buttonTransl, &QPushButton::clicked, [=]()
    {
        ui->openGLWidget->polyhedrons[ui->spinObjectID->value()].Translate(ui->spinTranslDx->value(), ui->spinTranslDy->value(), ui->spinTranslDz->value());
        ui->openGLWidget->repaint();
    });
}

GLWindow::~GLWindow()
{
    delete ui;
}
