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
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    PBD::Sphere * sphere=new PBD::Sphere(0.7, glm::vec3(1,0,0));
    Cloth.addObjectToList(sphere);
    Cloth.initialize(glm::vec3(-0.5,2,0.5), 20, 20, 0.1, 1);

    Cloth.changePointMass(0,0);
    Cloth.changePointMass(Cloth.m_width*(Cloth.m_height-1),0);
}

void GLWidget::paintGL()
{
    Cloth.runSolver(0.01);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1, 0, 0.5);

    glPushMatrix();
        auto p=Cloth.OtherObjs[0]->m_pos;
        glTranslated(p.x,p.y,p.z);
        //glutSolidSphere(Cloth.OtherObjs[0]->m_radius,20,20);
    glPopMatrix();

    glBegin(GL_LINES);
    for(uint i=0; i<Cloth.m_ConPtrs.size(); i++)
    {
        auto pA=Cloth.m_ConPtrs[i]->m_pA->m_ppos;
        auto pB=Cloth.m_ConPtrs[i]->m_pB->m_ppos;

        glColor3f(1, 0, 0);
        glVertex3f(pA.x, pA.y, pA.z);
        glColor3f(0, 1, 0);
        glVertex3f(pB.x, pB.y, pB.z);
    }
    glEnd();

}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5,5,-5, 0,0,0, 0,1,0);
}
