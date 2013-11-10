#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtGui>
#include <map>
#include <XnCppWrapper.h>


    class GLWidget : public QGLWidget {
        QTimer *timer;
        Q_OBJECT // must include this if you use Qt signals/slots

    public:
        GLWidget(QWidget *parent = NULL);
        void updateGL();
        void setCurrentJointMap(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> newMap);

    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

    private:
        std::map<XnSkeletonJoint,XnSkeletonJointTransformation> currentJointMap;
    };

#endif // GLWIDGET_H
