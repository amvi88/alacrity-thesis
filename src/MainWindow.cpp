#include "MainWindow.hxx"
#include "ui_mainwindow.h"
#include <iostream>
#include <QtGui/QMessageBox>

//private
void MainWindow::enableProgressElements(int maxFrames ){
    ui->progressBar->setEnabled(true);
    ui->progressBar->setValue(0);
    ui->progressBar->setMaximum(maxFrames);

    ui->spinBoxFrame->setEnabled(true);
    ui->spinBoxFrame->setMaximum(maxFrames);
}


//Slots
void MainWindow::on_actionLoad_triggered()
{
    QString temp = QFileDialog::getOpenFileName(this, tr("Open File"), tr("/home"), tr("XML Files (*.xml)"));
    filename = temp.toUtf8().constData();
    currentFileName = filename;

    if (! filename.empty()){
        xmlManager.LoadDocument(filename);
        enableProgressElements(xmlManager.getMaxAmountOfFrames());
        StartPlayback();
    }
}

void MainWindow::on_actionSave_triggered()
{
    char fileName[100] = "";
    if (! isPlayback){
        char * date = getCurrentTimeDate();
        snprintf( fileName, sizeof(fileName), "%s%s%s%s%s",  "Recordings", "\/",  "Recording_", date ,".xml");
        delete date;
    }else{
        snprintf( fileName, sizeof(fileName), "%s%s%s%s",  "Recordings", "\/",  "Index", ".xml");
    }


    QString temp = QFileDialog::getSaveFileName(this, QObject::tr("Save XML File"), QObject::tr(fileName), QObject::tr("XML Files (*.xml)"));
    filename = temp.toUtf8().constData();
    currentFileName = filename;

    if (! filename.empty()){
        if (!isPlayback){
            xmlManager.SaveDocument(filename);
        }else{
            gestureIndexWriter.Save();
        }
    }
}

void MainWindow::on_actionExit_triggered()
{
    finalize();
    this->close();
}

void MainWindow::closeEvent( QCloseEvent* ){
    finalize();

}

void MainWindow::finalize(){
    xmlManager.CloseDocument();
    gestureIndexWriter.Finalize();
    if (assistantThread){
        assistantThread->quit();
        assistantThread->wait();
    }
    this->close();
}

 void MainWindow::keyPressEvent(QKeyEvent* event){

    if (isPlayback){
        if (event->key()==Qt::Key_P)
        {
            if (drawTimer->isActive()){
                drawTimer->stop();
            }else{
                connect(drawTimer, SIGNAL(timeout()), this, SLOT(displayPlaybackData()));
                drawTimer->start(1000/30);
            }
        }
        else if (event->key()==Qt::Key_Left){
            forwardAdvance = false;
            displayPlaybackData();
        }
        else if (event->key()==Qt::Key_Right){
            forwardAdvance = true;
            displayPlaybackData();
        }
    }
 }


void MainWindow::on_pushButton_clicked()
{
    mustTrackFrames = ! mustTrackFrames;
    if (mustTrackFrames && !startedToRecord){
        startedToRecord = true;
        recordingTimeOut = new QTimer(this);
        recordingTimeOut->setSingleShot(true);
        connect(recordingTimeOut, SIGNAL(timeout()), this, SLOT(endFrameTrackingDuetoTimeLimit()));
        recordingTimeOut->start(60000);
    }else if (!mustTrackFrames && startedToRecord){
        if (recordingTimeOut){
             	recordingTimeOut->stop();
        }
        emit timeLimitReached();
    }

}

void MainWindow::on_comboBoxAlgorithm_currentIndexChanged(const QString &arg1)
{
    algorithm = arg1.toUtf8().constData();
}

void MainWindow::on_comboBoxGesture_currentIndexChanged(const QString &arg1)
{
    gestureType = arg1.toUtf8().constData();
}

void MainWindow::on_comboBoxHand_currentIndexChanged(const QString &arg1){
    handFocus = arg1.toUtf8().constData();
}

void MainWindow::on_spinBoxFrame_valueChanged(int arg1)
{
    if (isPlayback){
        xmlManager.SetCurrentFrame(arg1);
        if (!drawTimer->isActive()){
            displayPlaybackData();
        }
    }
}

void MainWindow::on_toolButtonStart_clicked()
{
    if (isPlayback){
        StartFrame = ui->progressBar->value();
    }
}




void MainWindow::on_toolButtonStop_clicked()
{
    bool timerActive = false;

    if (isPlayback){
        StopFrame = ui->progressBar->value();
    }

    if (drawTimer->isActive()){
       drawTimer->stop();
       timerActive = true;
    }

    if (handFocus == "Left"){
        gestureIndexWriter.AddGestureEntry(gestureType,  "Left",  XN_SKEL_LEFT_HAND, currentFileName, StartFrame, StopFrame );
    }
    else if (handFocus == "Right"){
        gestureIndexWriter.AddGestureEntry(gestureType, "Right", XN_SKEL_RIGHT_HAND, currentFileName, StartFrame, StopFrame );
    }else{
        gestureIndexWriter.AddGestureEntry(gestureType,  "Left",  XN_SKEL_LEFT_HAND, currentFileName, StartFrame, StopFrame );
        gestureIndexWriter.AddGestureEntry(gestureType, "Right", XN_SKEL_RIGHT_HAND, currentFileName, StartFrame, StopFrame );
    }
    if (timerActive){
       connect(drawTimer, SIGNAL(timeout()), this, SLOT(displayPlaybackData()));
       drawTimer->start(1000/30);
    }
}

//Events


void MainWindow::processNewFrameEvent(std::map<XnSkeletonJoint,XnSkeletonJointTransformation> frameData){
    if (! isPlayback){
        ui->skeletonWidget->setCurrentJointMap(frameData);
    }

    if (mustTrackFrames && !stoppedRecording && startedToRecord){
        xmlManager.AddFrameData(frameData);
    }
}

void MainWindow::StartPlayback(){

    if (assistantThread){
        assistantThread->quit();
        assistantThread->wait();
    }


    xmlManager.SetCurrentFrame(0);
    isPlayback = true;
    forwardAdvance = true;
    drawTimer = new QTimer(this);
    connect(drawTimer, SIGNAL(timeout()), this, SLOT(displayPlaybackData()));
    drawTimer->start(1000/30);

};


void MainWindow::endFrameTrackingDuetoTimeLimit(){
    if (mustTrackFrames && startedToRecord){
        mustTrackFrames = false;
        stoppedRecording = true;

        QMessageBox::warning(0, "Recording Ended", "Recording of user tracking was ended due to the established time limit, or due to the user selection", QMessageBox::Ok);
        on_actionSave_triggered();

        enableProgressElements(xmlManager.getMaxAmountOfFrames());
        StartPlayback();
    }
}

void MainWindow::displayPlaybackData(){
    ui->skeletonWidget->setCurrentJointMap(xmlManager.GetPositionDataFromCurrentFrame());

    if (forwardAdvance){
        ui->progressBar->setValue(ui->progressBar->value()+1);
        xmlManager.AdvanceFrame();
    }else{
        if (ui->progressBar->value() > 0){
            ui->progressBar->setValue(ui->progressBar->value()-1);
        }
        xmlManager.RewindFrame();
    }
}


char * MainWindow::getCurrentTimeDate(){
    time_t rawtime;
    struct tm * timeinfo;

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    char *buffer = new char[14];
    strftime (buffer,14,"%Y%m%d%H%M",timeinfo);
    return buffer;
}

//Constructor & destructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(this, SIGNAL(timeLimitReached()), this, SLOT(endFrameTrackingDuetoTimeLimit()));
    xmlManager.InitializeDocument("UserTracking");
    gestureIndexWriter.Init();
}



MainWindow::~MainWindow()
{
    delete ui;
}


