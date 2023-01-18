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
typedef std::basic_string<char, std::char_traits<char>, std::allocator<char>>
    MojString;
int main(int argc, char* argv[])
{
    QString q_pixmap_path = "";
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

    std::cout << led_number << "\t" << led_size << "\t" << angle << "\t"
              << pixmap_path << std::endl;

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    QPixmap pix_map;
    pix_map.load(q_pixmap_path);

    Interpolator interpolator_obj(&app);
    Transform transform_obj({100, 100}, 1);
    interpolator_obj.setPixmap(&pix_map);

    return 0;
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