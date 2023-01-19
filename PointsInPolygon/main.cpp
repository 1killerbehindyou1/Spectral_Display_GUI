#include "Interpolator.h"
#include <QDebug>
#include <QGuiApplication>
#include <chrono>
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
typedef std::basic_string<char, std::char_traits<char>, std::allocator<char>>
    MojString;

int main(int argc, char* argv[])
{

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    std::string pixmap_path = "";
    int led_number = 0;
    int led_size = 0;
    int angle = 0;

    for (int i = 0; i < argc; i++)
    {
        std::string parsed_arg(argv[i]);

        if (parsed_arg.find("--led-number=") != std::string::npos)
        {
            led_number =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--led-size=") != std::string::npos)
        {
            led_size = std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--angle=") != std::string::npos)
        {
            angle = std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--image-path=") != std::string::npos)
        {
            pixmap_path = parsed_arg.erase(0, parsed_arg.find("=") + 1);
        }
    }
    if (led_number == 0)
    {
        led_number = 250;
    }
    if (angle == 0)
    {
        angle = 1;
    }
    if (led_size == 0)
    {
        led_size = 1;
    }
    if (pixmap_path == "")
    {
        pixmap_path = "C:\\Users\\mplesniak\\Pictures\\BITMAPA.png";
    }
    std::cout << "parameters:\nled numer: " << led_number
              << "\tled_size: " << led_size << "\tangle: " << angle
              << "\tpixmap_path: " << pixmap_path << std::endl;

    QPixmap pix_map;
    pix_map.load(QString::fromStdString(pixmap_path));

    Interpolator interpolator_obj(&app);
    interpolator_obj.setPixmap(&pix_map);

    QRect rect{QPoint{led_size * 0.5, led_size * (-0.5)},
               QSize{led_size, led_size}};
    Transform transform_obj(QPoint{pix_map.width() / 2, pix_map.height() / 2},
                            angle); // centrum obrotu w centrum obrazka

    QVector<QPointF> vector_transformed_points(
        interpolator_obj.interpolatorTransform(transform_obj, rect));

    qDebug() << pix_map;
    qDebug() << vector_transformed_points;
    return 0;
}
