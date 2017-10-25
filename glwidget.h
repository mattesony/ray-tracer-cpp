#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>

class GLWidget :
        public QOpenGLWidget,
        protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
    void teardownGL();

private:
     // Private Helpers
    void printContextInformation();

};
