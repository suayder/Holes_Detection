/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <eventmouseclass.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *Salve_DBF;
    QAction *actionExit;
    QWidget *centralWidget;
    QLabel *labelStatus;
    QRadioButton *trainig;
    QRadioButton *operation;
    QFrame *line;
    QListWidget *imageList;
    EventMouseClass *graphicsView;
    QLabel *label;
    QLineEdit *lineInputBits;
    QPushButton *ButtonInputRamBits;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLabel *numberRans;
    QPushButton *StartTrain;
    QLabel *points;
    QLabel *x1;
    QLabel *y1;
    QLabel *x2;
    QLabel *y2;
    QMenuBar *menuBar;
    QMenu *menuOptions;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1089, 624);
        MainWindow->setMouseTracking(false);
        Salve_DBF = new QAction(MainWindow);
        Salve_DBF->setObjectName(QStringLiteral("Salve_DBF"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelStatus = new QLabel(centralWidget);
        labelStatus->setObjectName(QStringLiteral("labelStatus"));
        labelStatus->setGeometry(QRect(10, 10, 59, 20));
        trainig = new QRadioButton(centralWidget);
        trainig->setObjectName(QStringLiteral("trainig"));
        trainig->setGeometry(QRect(60, 10, 71, 20));
        operation = new QRadioButton(centralWidget);
        operation->setObjectName(QStringLiteral("operation"));
        operation->setGeometry(QRect(140, 10, 100, 20));
        line = new QFrame(centralWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 30, 211, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        imageList = new QListWidget(centralWidget);
        imageList->setObjectName(QStringLiteral("imageList"));
        imageList->setGeometry(QRect(10, 330, 211, 161));
        graphicsView = new EventMouseClass(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(230, 10, 851, 481));
        graphicsView->setMouseTracking(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(13, 51, 110, 16));
        lineInputBits = new QLineEdit(centralWidget);
        lineInputBits->setObjectName(QStringLiteral("lineInputBits"));
        lineInputBits->setGeometry(QRect(130, 50, 51, 22));
        ButtonInputRamBits = new QPushButton(centralWidget);
        ButtonInputRamBits->setObjectName(QStringLiteral("ButtonInputRamBits"));
        ButtonInputRamBits->setGeometry(QRect(180, 50, 41, 22));
        ButtonInputRamBits->setMaximumSize(QSize(80, 16777215));
        ButtonInputRamBits->setIconSize(QSize(16, 16));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 80, 211, 16));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(13);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        numberRans = new QLabel(layoutWidget);
        numberRans->setObjectName(QStringLiteral("numberRans"));

        horizontalLayout->addWidget(numberRans);

        StartTrain = new QPushButton(centralWidget);
        StartTrain->setObjectName(QStringLiteral("StartTrain"));
        StartTrain->setGeometry(QRect(10, 280, 211, 41));
        points = new QLabel(centralWidget);
        points->setObjectName(QStringLiteral("points"));
        points->setGeometry(QRect(10, 100, 61, 21));
        x1 = new QLabel(centralWidget);
        x1->setObjectName(QStringLiteral("x1"));
        x1->setGeometry(QRect(60, 100, 71, 21));
        y1 = new QLabel(centralWidget);
        y1->setObjectName(QStringLiteral("y1"));
        y1->setGeometry(QRect(130, 100, 81, 21));
        x2 = new QLabel(centralWidget);
        x2->setObjectName(QStringLiteral("x2"));
        x2->setGeometry(QRect(60, 120, 71, 16));
        y2 = new QLabel(centralWidget);
        y2->setObjectName(QStringLiteral("y2"));
        y2->setGeometry(QRect(130, 120, 81, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1089, 19));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QStringLiteral("menuOptions"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuOptions->menuAction());
        menuOptions->addAction(Salve_DBF);
        menuOptions->addAction(actionExit);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Prototype", 0));
        Salve_DBF->setText(QApplication::translate("MainWindow", "Salve Image Info (JSON)", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        labelStatus->setText(QApplication::translate("MainWindow", "Status:", 0));
        trainig->setText(QApplication::translate("MainWindow", "Trainig", 0));
        operation->setText(QApplication::translate("MainWindow", "Operation", 0));
        label->setText(QApplication::translate("MainWindow", "RAM Number Bits:", 0));
        lineInputBits->setText(QApplication::translate("MainWindow", "7", 0));
        ButtonInputRamBits->setText(QApplication::translate("MainWindow", "Input", 0));
        label_2->setText(QApplication::translate("MainWindow", "Number of RAMs:", 0));
        numberRans->setText(QString());
        StartTrain->setText(QApplication::translate("MainWindow", "Start Train", 0));
        points->setText(QApplication::translate("MainWindow", "Points:", 0));
        x1->setText(QApplication::translate("MainWindow", "x1:", 0));
        y1->setText(QApplication::translate("MainWindow", "y1:", 0));
        x2->setText(QApplication::translate("MainWindow", "x2:", 0));
        y2->setText(QApplication::translate("MainWindow", "y2:", 0));
        menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
