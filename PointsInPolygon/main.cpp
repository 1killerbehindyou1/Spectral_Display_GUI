#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQuick>
#include <iostream>
//#include <QDebug>

void myMessageOutput(QtMsgType type,
                     [[maybe_unused]] const QMessageLogContext &context,
                     const QString &msg) {
  QByteArray localMsg = msg.toLocal8Bit();
  QString typeStr = "OTHER";
  switch (type) {
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
    std::cout
      << QString("%1: %2").arg(typeStr).arg(localMsg.constData()).toStdString()
      << std::endl;
}


int main(int argc, char *argv[]){
   
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);
    app.setOrganizationName("1killerbehindyou1");
    app.setOrganizationDomain("Education");
    
    //qmlRegisterType<LedRuler>("Main", 1, 0, "LedRuler");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl) QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}