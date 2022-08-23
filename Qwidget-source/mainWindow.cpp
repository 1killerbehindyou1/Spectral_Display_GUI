#include "MainWindow.h"
#include "./ui_MainWindow.h"
#include <QDebug>
#include <QRect>
#include <QColor>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap("C:\\Users\\mplesniak\\Desktop\\1. Mentoring_QT_project\\Spectral_Display_GUI\\Pictures\\szachy.png");
    
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::paintEvent(QPaintEvent * e)
{

}
 