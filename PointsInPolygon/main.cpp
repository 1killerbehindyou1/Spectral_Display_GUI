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

QVector<QString> parseArgs(int argc, char* argv[]) {
    QVector<QString> result;
    std::copy(argv, argv + argc, std::back_inserter(result));
    return result;
}


QColor operator*(const QColor& color, double factor) {
    return {qRgba(color.red() * factor, color.green() * factor, color.blue() * factor, color.alpha())};
}

QColor operator*(double factor, const QColor& color) {
    return color * factor;
}

QColor operator+(const QColor& color1, const QColor& color2) {
    return {qRgba(color1.red() + color2.red(), color1.green() + color2.green(), color1.blue() + color2.blue(), (color1.alpha() + color2.alpha())/2)};
}

QColor computeAverageColor(QColor currentAverage, std::size_t aggregatedPoints, QColor newColor) {
    double oldFactor = static_cast<double>(aggregatedPoints) / (aggregatedPoints + 1);
    double newFactor = 1.0 / (aggregatedPoints + 1);
    return currentAverage * oldFactor + newFactor * newColor;
}


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
        //--led-number 1
        //--led-number=1
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
              << "\tpixmap_path: " << pixmap_path << "\n"
              << std::endl;

    QPixmap pix_map;
    pix_map.load(QString::fromStdString(pixmap_path));

    Interpolator interpolator_obj(&app);
    interpolator_obj.setPixmap(&pix_map);

    QRect rect{QPoint{led_size * 0.5, led_size * (-0.5)},
               QSize{led_size, led_size}};

    // centrum obrotu w centrum obrazka
    QPoint rot_centr(pix_map.width() / 2, pix_map.height() / 2);

    QColor averageColor{};
    std::size_t numberOfAgregatedColors;

    // Start measuring time on transforation points
    auto begin = std::chrono::high_resolution_clock::now();

    int amout_of_calc_points = 0;

    for (int rot = 0; rot < 360; rot += angle)
    {
        for (int i = 0; i < led_number; i++)
        {
            rect.moveTo(rect.topLeft() + QPoint{led_size, 0});

            QColor color = interpolator_obj.interpolatorSetLedColor(
                interpolator_obj.interpolatorTransform(
                    Transform{rot_centr, angle}, rect));
//            averageColor = computeAverageColor(averageColor, numberOfAgregatedColors, color);
//            ++numberOfAgregatedColors;
            amout_of_calc_points += led_size * led_size;
        }
    }
    // Stop measuring time on transformation points and calculate the
    // elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed =
//        std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        std::chrono::duration_cast<std::chrono::duration<double, std::micro>>(end - begin);

    qDebug() << "Time on transformation points:\t" << elapsed.count() / 1000
             << "miliseconds";
    qDebug() << "aproximation of transformed point amout:\t" << amout_of_calc_points
             << "\n";
    qDebug() << "Average color:" << averageColor;
    qDebug() << pix_map;

    return 0;
}
