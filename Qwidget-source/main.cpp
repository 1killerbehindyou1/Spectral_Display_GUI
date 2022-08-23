#include <iostream>
#include "Tmatrix.h"
#include <QApplication>
#include <QRect>
#include <QMainWindow>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    //QRect r1(100, 200, 11, 16);


    return a.exec();
    
}
