#include "glwindow.h"
#include "ui_glwindow.h"

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonLoad,&QPushButton::clicked,[=]() { ui->openGLWidget->OpenData((ui->lineEditFilename->text()).toUtf8().constData()); ui->openGLWidget->repaint();});
    QObject::connect(ui->buttonXYProj,&QPushButton::clicked,[=](bool toggled) { if(toggled) ui->openGLWidget->setProjection("XY"); ui->openGLWidget->repaint(); });
    QObject::connect(ui->buttonXZProj,&QPushButton::clicked,[=](bool toggled) { if(toggled) ui->openGLWidget->setProjection("XZ"); ui->openGLWidget->repaint(); });
    QObject::connect(ui->buttonYZProj,&QPushButton::clicked,[=](bool toggled) { if(toggled) ui->openGLWidget->setProjection("YZ"); ui->openGLWidget->repaint(); });
}

GLWindow::~GLWindow()
{
    delete ui;
}
