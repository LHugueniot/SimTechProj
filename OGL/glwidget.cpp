#include "glwidget.h"
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(16);

}

void GLWidget::initializeGL()
{
    glClearColor(0.2,0.2,0.2,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    Cloth.initialize(glm::vec3(0,0,0), 3, 3, 0.5);
}

void GLWidget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    glBegin(GL_TRIANGLES);
//    glColor3f(1, 1, 0);
//    glVertex3f(1,0,0);

//    glColor3f(1, 1, 0);
//    glVertex3f(0,1,0);

//    glColor3f(1, 1, 0);
//    glVertex3f(1,1,0);
//    glEnd();
    /*
    for(uint i=0; i<Cloth.m_PointsPtr->m_ppos.size()/3; i++)
    {
            int a=i*3;
            glBegin(GL_TRIANGLES);
            glColor3f(1, 0, 0);
            glVertex3f(Cloth.m_PointsPtr->m_ppos[a].x, Cloth.m_PointsPtr->m_ppos[a].y, Cloth.m_PointsPtr->m_ppos[a].z);
            //glNormal3f(1,1,1);

            glColor3f(0, 1, 0);
            glVertex3f(Cloth.m_PointsPtr->m_ppos[a+1].x, Cloth.m_PointsPtr->m_ppos[a+1].y, Cloth.m_PointsPtr->m_ppos[a+1].z);
            //glNormal3f(0,0,0);

            glColor3f(0, 0, 1);
            glVertex3f(Cloth.m_PointsPtr->m_ppos[a+2].x, Cloth.m_PointsPtr->m_ppos[a+2].y, Cloth.m_PointsPtr->m_ppos[a+2].z);
            //glNormal3f(0,0,0);
            glEnd();
            //std::cout<<i<<"\n";
    }
    */
    //important functions
    //glRotatef(0.5,1,1,1);
    //glutSolidTeapot(0.8);
    //glTranslatef(0 , 0.01, 0);

}
void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0,0,0, 0,1,0);
}
