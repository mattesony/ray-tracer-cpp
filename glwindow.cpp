#include "glwindow.h"
#include "ui_glwindow.h"

GLWindow::GLWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GLWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->buttonLoad,&QPushButton::clicked,[=]() { ui->openGLWidget->OpenData((ui->lineEditFilename->text()).toUtf8().constData()); });
}

GLWindow::~GLWindow()
{
    delete ui;
}
