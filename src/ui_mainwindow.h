/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.0.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H


#include <QtCore/QVariant>
#include <QtGui>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <QtOpenGL/QGLWidget>
#include <QFileDialog>


#include "GLWidget.hxx"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:

    std::string filename;


    QAction *actionLoad;
    QAction *actionSave;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QComboBox *comboBoxAlgorithm;
    QComboBox *comboBoxGesture;
    QSpinBox *spinBoxFrame;
    QLabel *labelFrame;
    QLabel *labelChangeFrame;
    QLabel *labelAlgorithm;
    QLabel *labelGesture;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menuExport;
    QStatusBar *statusbar;
    QToolButton *toolButtonStart;
    QToolButton *toolButtonStop;

    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    GLWidget *skeletonWidget;
    QTimer* timer;

    QLabel *labelHand;
    QComboBox *comboBoxHand;

    QMainWindow * parentWindow;

    void setupUi(QMainWindow *MainWindow);
    void retranslateUi(QMainWindow *MainWindow);


};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
