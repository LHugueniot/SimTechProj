#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include <QObject>
#include <QGLWidget>
#include <QTimer>
#include <glm/glm.hpp>

#include <clothobj.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent=0);
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    PBD::ClothObj Cloth;
private:
    QTimer timer;
};

#endif // GLWIDGET_H
