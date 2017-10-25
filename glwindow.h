#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QMainWindow>
#include "Polyhedron.h"

namespace Ui {
class GLWindow;
}

class GLWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GLWindow(QWidget *parent = 0);
    ~GLWindow();
    void OpenData(std::string filename);

private:
    Ui::GLWindow *ui;
    std::vector<Polyhedron> polyhedrons;
};

#endif // GLWINDOW_H
