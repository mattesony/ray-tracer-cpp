#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
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
    Ui::GLWindow *ui;
    GLWidget *glWidget;
};

#endif // GLWINDOW_H
