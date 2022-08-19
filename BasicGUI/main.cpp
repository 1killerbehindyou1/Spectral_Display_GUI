#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <iostream>
#include <QDebug>
//#include "Led_Matrix.h"
//#include "PieChart.h"

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
   
    QByteArray localMsg = msg.toLocal8Bit();
    const char *file = context.file ? context.file : "";
    const char *function = context.function ? context.function : "";
    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtInfoMsg:
        fprintf(stdout, "Info: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtWarningMsg:
        fprintf(stdout, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtCriticalMsg:
        fprintf(stdout, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    case QtFatalMsg:
        fprintf(stdout, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), file, context.line, function);
        break;
    }
}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //std::cout<< "================";
    //Led_Matrix *matrix = new Led_Matrix();  //<==============================
    
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    qDebug()<< "XXXXXXXXXXXXXXXXXXXXXXX";
    qInstallMessageHandler(myMessageOutput);
    qmlRegisterType<Led_Matrix>("Main", 1, 0, "Led_Matrix");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("_matrix", matrix);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app, [url](QObject *obj, const QUrl &objUrl) {if (!obj && url == objUrl)QCoreApplication::exit(-1);}, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();
}
