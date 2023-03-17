#include "BenchmarkMeasuredTask.hpp"
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QGuiApplication>
#include <QImage>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>

struct Parameters
{
    QFileInfo pixmap_path{"C:\\Users\\mplesniak\\Pictures\\BITMAPA.png"};
    int led_number{100};
    int led_size{5};
    int angle{1};
    int iteration{100};
    QFileInfo output_path{
        "C:\\Users\\mplesniak\\Pictures\\BITMAPA_transformed.png"};
};
namespace benchmark
{
using algorithm = QImage (*)(int, int, int, const std::string&);

void myMessageOutput(QtMsgType type,
                     [[maybe_unused]] const QMessageLogContext& context,
                     const QString& msg);

int measureStatisticTime(algorithm fun, const Parameters& param);
Parameters argParsing(int argc, char* argv[]);

} // namespace benchmark
