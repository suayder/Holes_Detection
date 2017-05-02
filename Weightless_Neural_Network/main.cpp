/************************************************************************************
 *                                                                                  *
 *  Project created by QtCreator 2017-03-17T17:57:23                                *
 *  Author: Suayder Milhomem Costa                                                  *
 * Compile information: This aplication use c++11 version to compile                *
 *                                                                                  *
 ************************************************************************************/


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
