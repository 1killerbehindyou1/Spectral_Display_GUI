#include "FileManager.hpp"
#include "LiveImageProvider.hpp"
#include "ProcessMonitor.hpp"
#include "RenderEngine.hpp"
#include "RenderSelector.hpp"
#include "SettingsManager.hpp"
#include "TransformEngine.hpp"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSettings>
#include <QtQuick>

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

    const QString current_path = QDir::currentPath();
    const QString legacy_settings_root =
        QDir::cleanPath(current_path + QStringLiteral("/.config"));
    const QString project_settings_root = QDir::cleanPath(
        current_path + QStringLiteral("/SpectralDisplayPro/.config"));

    const QString legacy_conf_path =
        QDir::cleanPath(legacy_settings_root +
                        QStringLiteral("/1killerbehindyou1/BasicGUI.conf"));
    const QString project_conf_path =
        QDir::cleanPath(project_settings_root +
                        QStringLiteral("/1killerbehindyou1/BasicGUI.conf"));

    QDir().mkpath(QFileInfo(project_conf_path).path());

    if (QFile::exists(legacy_conf_path) && !QFile::exists(project_conf_path))
    {
        if (!QFile::rename(legacy_conf_path, project_conf_path))
        {
            if (QFile::copy(legacy_conf_path, project_conf_path))
            {
                QFile::remove(legacy_conf_path);
            }
        }
    }

    QSettings::setPath(QSettings::IniFormat, QSettings::UserScope,
                       project_settings_root);
    QSettings::setPath(QSettings::NativeFormat, QSettings::UserScope,
                       project_settings_root);

#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_DisableHighDpiScaling);
#endif

    qInstallMessageHandler(myMessageOutput);
    QGuiApplication app(argc, argv);

    app.setOrganizationName("1killerbehindyou1");
    app.setOrganizationDomain("Education");

    QSettings startup_settings;
    startup_settings.setValue(QStringLiteral("runtime/lastLaunchEpochMs"),
                              QDateTime::currentMSecsSinceEpoch());
    startup_settings.sync();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    qmlRegisterType<RenderEngine>("Main", 1, 0, "RenderEngine");
    qmlRegisterType<RenderSelector>("Main", 1, 0, "Selector");

    qRegisterMetaType<QPixmap*>("QPixmap*");
    qRegisterMetaType<QImage*>("QImage*");

    FileManager file_manager(&app);
    engine.rootContext()->setContextProperty("file_manager", &file_manager);

    SettingsManager settings_manager(&app);
    engine.rootContext()->setContextProperty("settings_manager",
                                             &settings_manager);

    TransformEngine transform_engine(&app);
    engine.rootContext()->setContextProperty("transform_engine",
                                             &transform_engine);

    ProcessMonitor process_monitor(&app);
    engine.rootContext()->setContextProperty("process_monitor",
                                             &process_monitor);

    auto provider = new LiveImageProvider();
    engine.addImageProvider("live", provider);

    QObject::connect(
        &file_manager, &FileManager::fileReadyToTransform, &transform_engine,
        [&transform_engine](QPixmap pixmap)
        {
            auto shared_pixmap = std::make_shared<QPixmap>(std::move(pixmap));
            transform_engine.setPixmap(shared_pixmap);
            transform_engine.transformImage();
        });

    QObject::connect(&transform_engine, &TransformEngine::transformReady,
                     [provider](std::shared_ptr<QImage> image)
                     { provider->setImage(*image); });

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
