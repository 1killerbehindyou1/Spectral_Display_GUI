#include "../SinglePointTransform_lib/Interpolator.h"
#include <QDebug>
#include <QGuiApplication>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

struct Parameters
{
    std::string pixmap_path{"C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"};
    int led_number{100};
    int led_size{5};
    int angle{1};
    int iteration{100};
};

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
                             const std::string& pixmap_path)
{
    QPixmap pix_map{};
    pix_map.load(QString::fromStdString(pixmap_path));
    Interpolator interpolator_obj{};

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

using algorithm = void (*)(int, int, int, const std::string&);

int measureStatisticTime(algorithm fun, const Parameters& param)
{
    std::vector<double> average_cont{};

    for (int i = 0; i < param.iteration; i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        fun(param.led_number, param.led_size, param.angle, param.pixmap_path);
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

Parameters argParsing(int argc, char* argv[])
{
    Parameters run_params{};

    for (int i = 0; i < argc; i++)
    {
        std::string parsed_arg(argv[i]);
        if (parsed_arg.find("--iteration-number=") != std::string::npos)
        {
            run_params.iteration =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        if (parsed_arg.find("--led-number=") != std::string::npos)
        {
            run_params.led_number =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--led-size=") != std::string::npos)
        {
            run_params.led_size =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--angle=") != std::string::npos)
        {
            run_params.angle =
                std::stoi(parsed_arg.erase(0, parsed_arg.find("=") + 1));
        }
        else if (parsed_arg.find("--image-path=") != std::string::npos)
        {
            run_params.pixmap_path =
                parsed_arg.erase(0, parsed_arg.find("=") + 1);
        }
    }
    std::cout << "Library: SinglePointTransform"
              << "\nparameters:\nled numer: " << run_params.led_number
              << "\tNo iteration: " << run_params.iteration
              << "\tled_size: " << run_params.led_size
              << "\tangle: " << run_params.angle
              << "\tpixmap_path: " << run_params.pixmap_path << "\n"
              << std::endl;

    return run_params;
}

int main(int argc, char* argv[])
{
    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    qDebug() << "Average time: "
             << measureStatisticTime(interpolatorMeasurement,
                                     argParsing(argc, argv))
             << "microseconds";

    return 0;
}
