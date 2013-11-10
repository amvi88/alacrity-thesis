#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QtGui/QMainWindow>
#include <QtGui/QFileDialog>

#include <string.h>
#include <map>
#include <XnCppWrapper.h>

#include <boost/bind.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/thread.hpp>

#include <stdio.h>
#include <time.h>


#include "XmlManager.hxx"
#include "XMLGestureRecognizer.hxx"
#include "QTSkeletonTrackerThread.h"
#include "GestureQueue.h"

using namespace boost;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    string filename;
    string currentFileName;
    string algorithm, handFocus, gestureType;

    int StartFrame, StopFrame;

    bool   mustTrackFrames;
    bool   isPlayback;
    bool   startedToRecord;
    bool   stoppedRecording;
    bool   forwardAdvance;

    QTimer * recordingTimeOut;
    QTimer * drawTimer;

    QTSkeletonTrackerThread * assistantThread;

    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

     void processNewFrameEvent(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> frameData);
     void StartPlayback();

signals:
    void timeLimitReached();
    void animateFrame();

protected :
    XmlManager xmlManager;
    GestureQueue gestureIndexWriter;
    void closeEvent( QCloseEvent* );
    void keyPressEvent(QKeyEvent* event);

private slots:
    void on_actionLoad_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_pushButton_clicked();
    void on_spinBoxFrame_valueChanged(int arg1);
    void on_toolButtonStart_clicked();
    void on_toolButtonStop_clicked();
    void on_comboBoxAlgorithm_currentIndexChanged(const QString &arg1);
    void on_comboBoxGesture_currentIndexChanged(const QString &arg1);
    void on_comboBoxHand_currentIndexChanged(const QString &arg1);
    void endFrameTrackingDuetoTimeLimit();
    void displayPlaybackData();

private:
    Ui::MainWindow *ui;
    void enableProgressElements(int maxFrames );
    void finalize();
    char* getCurrentTimeDate();

};

#endif // MAINWINDOW_HXX
