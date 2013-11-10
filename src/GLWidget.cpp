#include <QtGui/QMouseEvent>
#include "GLWidget.hxx"
#include "SkeletonTracker.hxx"
#include <stdio.h>
#include <iostream>

    GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
        if (! parent){
            timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
            timer->start(1000/30);
        }
    }

    void GLWidget::updateGL(){
        QGLWidget::updateGL();
    }

    void GLWidget::initializeGL() {
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_BLEND);
        glEnable(GL_POLYGON_SMOOTH);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClearColor(0, 0, 0, 0);
    }

    void GLWidget::resizeGL(int w, int h) {
        glViewport(0, 0, w, h);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    }

    void GLWidget::paintGL() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (currentJointMap.size() > 0 && g_DepthGenerator){
                XnPoint3D pt[10];
                pt[0] = currentJointMap[XN_SKEL_LEFT_HAND].position.position;
                pt[1] = currentJointMap[XN_SKEL_LEFT_ELBOW].position.position;
                pt[2] = currentJointMap[XN_SKEL_LEFT_SHOULDER].position.position;
                pt[3] = currentJointMap[XN_SKEL_RIGHT_SHOULDER].position.position;
                pt[4] = currentJointMap[XN_SKEL_RIGHT_ELBOW].position.position;
                pt[5] = currentJointMap[XN_SKEL_RIGHT_HAND].position.position;
                pt[6] = currentJointMap[XN_SKEL_HEAD].position.position;
                pt[7] = currentJointMap[XN_SKEL_NECK].position.position;
                pt[8] = currentJointMap[XN_SKEL_TORSO].position.position;
                pt[9] = currentJointMap[XN_SKEL_WAIST].position.position;


                g_DepthGenerator.ConvertRealWorldToProjective(10,pt, pt);


                glBegin(GL_LINE_STRIP);
                for (int i = 0; i < 6; i++){
                    if (i < 3){
                        glColor3f(1,0,0);
                    }else{
                        glColor3f(0,1,0);
                    }
                     glVertex2f(pt[i].X/480,  pt[i].Y/-640);
                }
                glEnd();

                glBegin(GL_LINE_STRIP);
                for (int i = 6; i < 9; i++){
                     glVertex2f(pt[i].X/480,  pt[i].Y/-640);
                }
                glEnd();

                float X, Y;

                glColor3f(0,0,1);
                for (int i = 0; i < 10; i++){
                    X=pt[i].X/480;
                    Y= pt[i].Y/-640;
                    glBegin(GL_QUADS);

                    glVertex2f(X+0.01,Y+0.01);
                    glVertex2f(X-0.01,Y+0.01);
                    glVertex2f(X-0.01,Y-0.01);
                    glVertex2f(X+0.01,Y-0.01);
                    glEnd();

                }
        }
    }

    void GLWidget::setCurrentJointMap(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> newMap){
        currentJointMap = newMap;
    }
