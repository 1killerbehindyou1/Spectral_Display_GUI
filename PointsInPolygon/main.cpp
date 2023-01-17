#include "Interpolator.h"
#include <QDebug>
#include <QGuiApplication>
#include <iostream>

void myMessageOutput(QtMsgType type,
                     [[maybe_unused]] const QMessageLogContext& context,
                     const QString& msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    QString typeStr = "OTHER";
    switch (type)
    {
        case QtDebugMsg:
            typeStr = "DBG";
            break;
        case QtInfoMsg:
            typeStr = "INF";
            break;
        case QtWarningMsg:
            typeStr = "WRN";
            break;
        case QtCriticalMsg:
            typeStr = "CRT";
            break;
        case QtFatalMsg:
            typeStr = "FTL";
            break;
    }
    std::cout << QString("%1: %2")
                     .arg(typeStr)
                     .arg(localMsg.constData())
                     .toStdString()
              << std::endl;
}

int main(int argc, char* argv[])
{

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    QPixmap pix_map;
    pix_map.load("C:\\Users\\mplesniak\\Pictures\\BITMAPA.png");

    Interpolator interpolator_obj(&app);
    Transform transform_obj({100, 100}, 1);
    interpolator_obj.setPixmap(&pix_map);

    return app.exec();
}
