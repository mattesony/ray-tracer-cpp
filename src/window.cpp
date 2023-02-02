#include "./window.h"

#include <Eigen/Eigen>

#include "./intersection.h"
#include "./ray.h"
#include "./sphere.h"
#include "./ui_window.h"
#include "./vector.h"
using Eigen::Vector3f;

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window) {
  ui->setupUi(this);
  this->canvas = new Canvas(PPM_WIDTH, PPM_HEIGHT);

  QObject::connect(ui->buttonSavePPM, &QPushButton::clicked, [=]() {
    this->canvas->writeFile(ui->lineEditPPMName->text().toUtf8().constData());
  });

  Repaint();
}

void Window::PaintTrajectory() {
  PPM_WIDTH = 900;
  PPM_HEIGHT = 550;
  this->canvas = new Canvas(PPM_WIDTH, PPM_HEIGHT);

  Vector3f position = {0, 0, 0};
  Vector3f velocity = Vector3f({1, 1.8, 0}).normalized() * 11.25;
  Vector3f env = Vector3f({-0.01, -0.1, 0});
  for (int tick = 0; tick < PPM_WIDTH; tick++) {
    this->canvas->writePixel(position(0), PPM_HEIGHT - 1 - position(1),
                             Vector3f(1, 0, 0));
    position = position + velocity;
    velocity = velocity + env;
  }
  this->canvas->writePixel(PPM_WIDTH - 1, PPM_HEIGHT - 1, Vector3f(0, 1, 0));
  this->canvas->writePixel(0, PPM_HEIGHT - 1, Vector3f(1, 0, 0));
  this->canvas->writePixel(PPM_WIDTH - 1, 0, Vector3f(0, 1, 1));
  this->canvas->writePixel(0, 0, Vector3f(1, 1, 1));
  image.loadFromData(this->canvas->getPPM().c_str());
  ui->labelImage->setPixmap(image);
  // TODO: lock aspect ratio
}

void Window::PaintSphereIntersect() {
  int canvas_pixels = 1000;
  PPM_WIDTH = canvas_pixels;
  PPM_HEIGHT = canvas_pixels;
  this->canvas = new Canvas(PPM_WIDTH, PPM_HEIGHT);

  float wall_size = 7;
  float wall_z = 10;
  Vector4f ray_origin = point(0, 0, -5);
  float wall_pixel_size = wall_size / canvas_pixels;
  float half = wall_size / 2;

  Vector3f color = Vector3f(1, 0, 0);
  Sphere shape = Sphere();

  for (int y = 0; y < canvas_pixels; y++) {
    float world_y = half - wall_pixel_size * y;
    for (int x = 0; x < canvas_pixels; x++) {
      float world_x = -half + wall_pixel_size * x;
      Vector4f position = point(world_x, world_y, wall_z);

      Ray r = Ray(ray_origin, (position - ray_origin).normalized());
      auto xs = shape.intersects(r);

      if (xs.size() > 0) {
        this->canvas->writePixel(x, y, color);
      }
    }
  }
  image.loadFromData(this->canvas->getPPM().c_str());
  ui->labelImage->setPixmap(image);
}

void Window::Repaint() { PaintSphereIntersect(); }

Window::~Window() { delete ui; }
