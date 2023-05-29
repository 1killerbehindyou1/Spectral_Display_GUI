#include "MeasurementTools.hpp"
#include "public/BenchmarkMeasuredTask.hpp"

int main(int argc, char* argv[])
{
    qInstallMessageHandler(benchmark::myMessageOutput);
    QGuiApplication app(argc, argv);

    qDebug() << "Average time: "
             << benchmark::measureStatisticTime(
                    interpolatorMeasurement, benchmark::argParsing(argc, argv))
             << "microseconds";

    return 0;
}
