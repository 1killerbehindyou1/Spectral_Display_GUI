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
    QString pixmap_path = "";
    int led_number;
    int led_size;
    int angle;

    // qDebug() << argc;
    // qDebug() << argv[0];

    if (argc == 1)
    {
        led_number = 250;
        led_size = 1;
        angle = 1;
        pixmap_path = "C:\\Users\\mplesniak\\Pictures\\BITMAPA.png";
        qDebug()
            << "application run with default parameters:"
            << "\npixmap_path = C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"
            << "\nled_number = 250 "
            << "\nled_size = 1"
            << "\nangle = 1";
    }
    else
    {
        for (int i = 1; i <= argc; ++i)
        {
        }
    }

    // This could be a sub method "parse(argc, argv)"
    /*
        String parameter = "";
        Boolean executed = false;

        for (i = 0; i < argc; ++i)
        {

            if element
                == "close"
                {
                    set parameter = argv[i + 1];
                    i++; // skip next element which was the parameter

                    // myCloseOperation would check if parameter is
                    // "all" for example and closes all windows
                    // or treat any other value as window title for
                    // example and closes only the matching window.
                    myCloseOperation(parameter);
                    set executed = true;
                }

            if element
                == "operation2"
                {
                    set parameter = argv[i + 1];
                    i++;

                    myOperation2Method(parameter);
                    set executed = true;
                }
        }

        if (executed == false)
        {
            showSyntaxErrorMessage();
            exit(1);
        }
    */
    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    QPixmap pix_map;
    pix_map.load(pixmap_path);
    // qDebug() << pix_map;

    Interpolator interpolator_obj(&app);
    Transform transform_obj({100, 100}, 1);
    interpolator_obj.setPixmap(&pix_map);

    return 0;
}
