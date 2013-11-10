#include "ui_mainwindow.h"
#include <QTranslator>
#include <QObject>
#include <iostream>

void Ui_MainWindow::setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");

        parentWindow = MainWindow;

        MainWindow->resize(957, 634);
        actionLoad = new QAction(MainWindow);
        actionLoad->setObjectName("actionLoad");
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName("actionAbout");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName("progressBar");
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(20, 560, 801, 23));
        progressBar->setMaximum(1800);
        progressBar->setValue(0);
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(10, 10, 131, 21));

        //Combo Boxes & Labels
        labelAlgorithm = new QLabel(centralwidget);
        labelAlgorithm->setObjectName(QString::fromUtf8("labelAlgorithm"));
        labelAlgorithm->setGeometry(QRect(160, 10, 71, 21));

        comboBoxAlgorithm = new QComboBox(centralwidget);
        comboBoxAlgorithm->setObjectName(QString::fromUtf8("comboBoxAlgorithm"));
        comboBoxAlgorithm->setGeometry(QRect(240, 10, 161, 25));

        labelGesture = new QLabel(centralwidget);
        labelGesture->setObjectName(QString::fromUtf8("labelGesture"));
        labelGesture->setGeometry(QRect(420, 10, 71, 21));

        comboBoxGesture = new QComboBox(centralwidget);
        comboBoxGesture->setObjectName(QString::fromUtf8("comboBoxGesture"));
        comboBoxGesture->setGeometry(QRect(480, 10, 121, 25));

        labelHand = new QLabel(centralwidget);
        labelHand->setObjectName(QString::fromUtf8("labelHand"));
        labelHand->setGeometry(QRect(620, 10, 71, 21));

        comboBoxHand = new QComboBox(centralwidget);
        comboBoxHand->setObjectName(QString::fromUtf8("comboBoxHand"));
        comboBoxHand->setGeometry(QRect(670, 10, 141, 25));

        //Spin box
        spinBoxFrame = new QSpinBox(centralwidget);
        spinBoxFrame->setObjectName("spinBoxFrame");
        spinBoxFrame->setEnabled(false);
        spinBoxFrame->setGeometry(QRect(850, 560, 91, 27));
        spinBoxFrame->setAccelerated(true);
        labelFrame = new QLabel(centralwidget);
        labelFrame->setObjectName(("labelFrame"));
        labelFrame->setGeometry(QRect(20, 540, 101, 21));
        labelChangeFrame = new QLabel(centralwidget);
        labelChangeFrame->setObjectName(("labelChangeFrame"));
        labelChangeFrame->setGeometry(QRect(840, 540, 101, 21));

        //Skeleton tracker
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 40, 930, 490));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        skeletonWidget = new GLWidget(verticalLayoutWidget);
        skeletonWidget->setObjectName(("SkeletonWidget"));
        skeletonWidget->resize(verticalLayoutWidget->width(),verticalLayoutWidget->height());
        //skeletonWidget->setAutoFillBackground(false);
        /*skeletonWidget->setGeometry(QRect(10, 60, 931, 481));
        skeletonWidget->setCursor(QCursor(Qt::OpenHandCursor));
        ;*/

        //START and STOP BUTTONS
        toolButtonStart = new QToolButton(centralwidget);
        toolButtonStart->setObjectName(QString::fromUtf8("toolButtonStart"));
        toolButtonStart->setGeometry(QRect(840, 10, 51, 25));
        toolButtonStop = new QToolButton(centralwidget);
        toolButtonStop->setObjectName(QString::fromUtf8("toolButtonStop"));
        toolButtonStop->setGeometry(QRect(893, 10, 51, 25));

        MainWindow->setCentralWidget(centralwidget);

        //MENU BAR
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(("menubar"));
        menubar->setGeometry(QRect(0, 0, 957, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(("menuFile"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(("menuAbout"));
        menuExport = new QMenu(menubar);
        menuExport->setObjectName(("menuExport"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuExport->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionLoad);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);
        QObject::connect(spinBoxFrame, SIGNAL(valueChanged(int)), progressBar, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);


        //refresh GL
        timer = new QTimer();
        QObject::connect(timer, SIGNAL(timeout()), skeletonWidget, SLOT(updateGL()));
        timer->start(1000/30);






    } // setupUi

void Ui_MainWindow::retranslateUi(QMainWindow *MainWindow)
{
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Alacrity Gesture Recorder", 0));
        actionLoad->setText(QApplication::translate("MainWindow", "Load", 0));
        actionSave->setText(QApplication::translate("MainWindow", "Save", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        progressBar->setFormat(QApplication::translate("MainWindow", "%v", 0));
        pushButton->setText(QApplication::translate("MainWindow", "Toggle Recording", 0));
        comboBoxAlgorithm->clear();
        comboBoxAlgorithm->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Angle quantification", 0)
         << QApplication::translate("MainWindow", "Bigdelou - Spine Based", 0)
         << QApplication::translate("MainWindow", "Bigdelou - Hierarchy Based", 0)
         << QApplication::translate("MainWindow", "DTW - Dynamic Time Warping", 0)
        );
        comboBoxGesture->clear();
        comboBoxGesture->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Wave Left", 0)
         << QApplication::translate("MainWindow", "Wave Right", 0)
         << QApplication::translate("MainWindow", "Wave Up", 0)
         << QApplication::translate("MainWindow", "Wave Down", 0)
         << QApplication::translate("MainWindow", "Diagonal Upper Left", 0)
         << QApplication::translate("MainWindow", "Diagonal Upper Right", 0)
         << QApplication::translate("MainWindow", "Diagonal Lower Left", 0)
         << QApplication::translate("MainWindow", "Diagonal Lower Right", 0)
         << QApplication::translate("MainWindow", "Zoom In", 0)
         << QApplication::translate("MainWindow", "Zoom Out", 0)
         << QApplication::translate("MainWindow", "Rotate Clockwise (Y axis)", 0)
         << QApplication::translate("MainWindow", "Rotate Counterclockwise (Y axis)", 0)
         << QApplication::translate("MainWindow", "Rotate Front", 0)
         << QApplication::translate("MainWindow", "Rotate Back", 0)
        );

        comboBoxHand->clear();
        comboBoxHand->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Left", 0)
         << QApplication::translate("MainWindow", "Right", 0)
         << QApplication::translate("MainWindow", "Both", 0)
        );

        labelFrame->setText(QApplication::translate("MainWindow", "Current Frame", 0));
        labelChangeFrame->setText(QApplication::translate("MainWindow", "Change Frame", 0));
        labelAlgorithm->setText(QApplication::translate("MainWindow", "Algorithm", 0, QApplication::UnicodeUTF8));
        labelGesture->setText(QApplication::translate("MainWindow", "Gesture", 0, QApplication::UnicodeUTF8));
        labelHand->setText(QApplication::translate("MainWindow", "Hand", 0, QApplication::UnicodeUTF8));

        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "Help", 0));
        menuExport->setTitle(QApplication::translate("MainWindow", "Export", 0));

        #ifndef QT_NO_TOOLTIP
        toolButtonStart->setToolTip(QApplication::translate("MainWindow", "Start Gesture", 0, QApplication::UnicodeUTF8));
        toolButtonStop->setToolTip(QApplication::translate("MainWindow", "Stop Gesture", 0, QApplication::UnicodeUTF8));
        #endif // QT_NO_TOOLTIP
        toolButtonStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        toolButtonStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));

} // retranslateUi
