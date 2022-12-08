#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "canvas.h"
#include "glwidget.h"


namespace Ui {
class GLWindow;
}

class GLWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GLWindow(QWidget *parent = 0);
    void Repaint();
    ~GLWindow();

private:
    int PPM_WIDTH = 200;
    int PPM_HEIGHT = 200;
    Ui::GLWindow *ui;
    GLWidget *glWidget;
    QPixmap image;
    Canvas *canvas;
};

#endif // GLWINDOW_H
