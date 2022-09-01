#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <iostream>
#include <QDebug>
#include "LedMatrix.h"

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
    

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);
    qmlRegisterType<LedMatrix>("Main", 1, 0, "LedMatrix");

    QQmlApplicationEngine engine;
    //engine.rootContext()->setContextProperty("_matrix", matrix);


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,&app, 
    [url](QObject *obj, const QUrl &objUrl) 
    {if (!obj && url == objUrl)QCoreApplication::exit(-1);}, Qt::QueuedConnection);
    engine.load(url);
    return app.exec();

}
