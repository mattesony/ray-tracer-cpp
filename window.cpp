#include "window.h"
#include "ui_window.h"
#include "Point.h"
#include "Vector.h"
#include <Eigen/Eigen>

using namespace Eigen;

Window::Window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);
    this->canvas = new Canvas(PPM_WIDTH, PPM_HEIGHT);

    QObject::connect(ui->buttonSavePPM, &QPushButton::clicked, [=]()
    {
        this->canvas->writeFile(ui->lineEditPPMName->text().toUtf8().constData());
    });

    Repaint();
}

void Window::Repaint()
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

Window::~Window()
{
    delete ui;
}
