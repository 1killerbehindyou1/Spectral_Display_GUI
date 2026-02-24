#include "FileManager.hpp"
#include "LedRuler.hpp"
#include "RenderSelector.hpp"
#include "TransformEngine.hpp"
#include "LiveImageProvider.hpp"

#include <QDebug>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QtQuick>
#include <thread>

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

int main(int argc, char* argv[])
{

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    app.setOrganizationName("1killerbehindyou1");
    app.setOrganizationDomain("Education");

    qmlRegisterType<LedRuler>("Main", 1, 0, "LedRuler");
    qmlRegisterType<RenderSelector>("Main", 1, 0, "Selector");

    qRegisterMetaType<QPixmap*>("QPixmap*");
    qRegisterMetaType<QImage*>("QImage*");

    FileManager file_manager(&app);
    engine.rootContext()->setContextProperty("file_manager", &file_manager);

    TransformEngine transform_engine(&app);
    engine.rootContext()->setContextProperty("transform_engine", &transform_engine);

    auto provider = new LiveImageProvider();
    engine.addImageProvider("live", provider);

    QObject::connect(&file_manager, &FileManager::fileReadyToTransform, &transform_engine,
                     [&transform_engine](QPixmap pixmap)
                     {
                         auto shared_pixmap = std::make_shared<QPixmap>(std::move(pixmap));
                         transform_engine.setPixmap(shared_pixmap);
                         transform_engine.transformImage(30, 1, 3, QPoint(0, 0));});

    QObject::connect(&transform_engine, &TransformEngine::transformReady,
                     [provider](std::shared_ptr<QImage> image)
                     {
                        provider->setImage(*image);
                     });

    QObject::connect(
        &engine, &QQmlApplicationEngine::objectCreated, &app,
        [url](QObject* obj, const QUrl& objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.load(url);
    return app.exec();
}
