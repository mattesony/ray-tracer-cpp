#ifndef WINDOW_H_
#define WINDOW_H_

#include <QMainWindow>
#include <QMessageBox>

#include "./canvas.h"

namespace Ui {
class Window;
}

class Window : public QMainWindow {
  Q_OBJECT

 public:
  explicit Window(QWidget *parent = 0);
  void Repaint();
  ~Window();
  void PaintTrajectory();
  void PaintSphereIntersect();
  void PaintSpherePhong();

 private:
  int PPM_WIDTH = 900;
  int PPM_HEIGHT = 550;
  Ui::Window *ui;
  QPixmap image;
  Canvas *canvas;
};

#endif  // WINDOW_H_
