#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "canvas.h"


namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    void Repaint();
    ~Window();

private:
    int PPM_WIDTH = 200;
    int PPM_HEIGHT = 200;
    Ui::Window *ui;
    QPixmap image;
    Canvas *canvas;
};

#endif // WINDOW_H
