#include "../Interpolator_lib/Interpolator.h"
#include <QDebug>
#include <QGuiApplication>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

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

void interpolatorMeasurement(int led_number, int led_size, int angle,
                             const std::string& pixmap_path, QObject* q_obj)
{
    QPixmap pix_map{};
    pix_map.load(QString::fromStdString(pixmap_path));
    Interpolator interpolator_obj{q_obj};

    interpolator_obj.setPixmap(&pix_map);

    QPoint rot_centr(pix_map.width() / 2, pix_map.height() / 2);

    QRect rect{QPoint{static_cast<int>(led_size * 0.5),
                      static_cast<int>(led_size * (-0.5))},
               QSize{led_size, led_size}};

    for (int rot = 0; rot < 360; rot += angle)
    {
        for (int i = 0; i < led_number; i++)
        {
            rect.moveTo(rect.topLeft() + QPoint{led_size, 0});

            QColor color = interpolator_obj.interpolatorSetLedColor(
                interpolator_obj.interpolatorTransform(
                    Transform{rot_centr, angle}, rect));
        }
    }
}

using algorithm = void (*)(int, int, int, const std::string&, QObject*);

int measureStatisticTime(int iteration, algorithm fun, int a, int b, int c,
                         const std::string& pixmap_path, QObject* q_obj)
{
    std::vector<double> average_cont{};

    for (int i = 0; i < iteration; i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        fun(a, b, c, pixmap_path, q_obj);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        average_cont.push_back(elapsed.count());
    }

    std::sort(average_cont.begin(), average_cont.end());
    average_cont.erase(average_cont.begin());
    average_cont.erase(average_cont.end() - 1);

    double sum{};
    for (double dd : average_cont)
    {
        sum += dd;
    }
    sum /= average_cont.size();
    return sum;
}

void argParsing(int argc, char* argv[], int& led_number, int& led_size,
                int& angle, int& iteration, std::string& pixmap_path)
{
    for (int i = 0; i < argc; i++)
    {
        std::string parsed_arg(argv[i]);
        if (parsed_arg.find("--iteration-number=") != std::string::npos)
        {
            iteration =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
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
    if (iteration == 0)
    {
        iteration = 100;
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
              << "\tpixmap_path: " << pixmap_path << "\n"
              << std::endl;
}

int main(int argc, char* argv[])
{

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    std::string pixmap_path{};
    int led_number{};
    int led_size{};
    int angle{};
    int iteration{};

    argParsing(argc, argv, led_number, led_size, angle, iteration, pixmap_path);

    qDebug() << "Average time: "
             << measureStatisticTime(iteration, interpolatorMeasurement,
                                     led_number, led_size, angle, pixmap_path,
                                     &app)
             << "microseconds";

    return 0;
}
