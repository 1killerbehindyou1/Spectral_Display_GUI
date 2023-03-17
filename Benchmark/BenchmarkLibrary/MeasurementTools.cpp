#include "MeasurementTools.hpp"
#include "BenchmarkMeasuredTask.hpp"

void benchmark::myMessageOutput(
    QtMsgType type, [[maybe_unused]] const QMessageLogContext& context,
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

using algorithm = QImage (*)(int, int, int, const std::string&);

int benchmark::measureStatisticTime(algorithm fun, const Parameters& param)
{
    std::vector<double> average_cont{};

    QImage result{};

    for (int i = 0; i < param.iteration; i++)
    {
        auto begin = std::chrono::high_resolution_clock::now();
        result = fun(param.led_number, param.led_size, param.angle,
                     param.pixmap_path.absoluteFilePath().toStdString());
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed =
            std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
        average_cont.push_back(elapsed.count());
    }

    qDebug() << result;
    result.save(param.output_path.absoluteFilePath());

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

Parameters benchmark::argParsing(int argc, char* argv[])
{
    Parameters run_params{};
    QString appName = QFileInfo{argv[0]}.baseName();
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
            run_params.pixmap_path = QString::fromStdString(
                parsed_arg.erase(0, parsed_arg.find("=") + 1));

            auto& path = run_params.pixmap_path;
            run_params.output_path =
                QFileInfo{path.dir(), QString("%1_%2_transformed.%3")
                                          .arg(path.baseName())
                                          .arg(appName)
                                          .arg(path.completeSuffix())};
        }
    }
    qDebug() << "Library: SinglePointTransform"
             << "\nparameters:\nled numer: " << run_params.led_number
             << "\tNo iteration: " << run_params.iteration
             << "\tled_size: " << run_params.led_size
             << "\tangle: " << run_params.angle
             << "\tpixmap_path: " << run_params.pixmap_path << "\n";

    return run_params;
}
