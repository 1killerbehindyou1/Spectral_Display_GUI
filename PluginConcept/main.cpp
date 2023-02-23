#include <iostream>

#include <vector>

#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>
#include <QLibrary>

#include "plugin_functions.h"
#include "plugin_api_helpers.h"

QFileInfoList listDir(const QDir& appDir)
{
    auto pluginsDir = QDir(appDir);
    pluginsDir.cd("plugins");

    return pluginsDir.entryInfoList({"*.dll"});
}

PluginApi* loadLibrary(const QFileInfo& fileInfo,
                       const Version& expectedApiVersion)
{
    auto filePath = fileInfo.absoluteFilePath();
    if (!fileInfo.exists())
    {
        qWarning().noquote()
            << QString("Given file '%1' doesn't exist").arg(filePath);
        return nullptr;
    }

    QLibrary sharedLibrary{filePath};
    sharedLibrary.setLoadHints(QLibrary::LoadHint::ExportExternalSymbolsHint);

    if (!sharedLibrary.load())
    {
        qWarning().noquote()
            << "Cannot load Shared Library:" << fileInfo.baseName();
        return nullptr;
    }

    auto getApiVersion = reinterpret_cast<GetApiVersion>(
        sharedLibrary.resolve("pluginApiVersion"));
    if (getApiVersion == nullptr)
    {
        qWarning().noquote()
            << QString("Shared Library '%1' is not a plugin")
                   .arg(fileInfo.baseName());
        return nullptr;
    }

    auto loadedApiVersion = getApiVersion();
    if (expectedApiVersion != loadedApiVersion)
    {
        qWarning().noquote()
            << QString(
                   "Shared Library '%1' is an incompatible plugin; "
                   "loaded version: '%2'; expected version: '%3'")
                   .arg(fileInfo.baseName())
                   .arg(toString(loadedApiVersion))
                   .arg(toString(expectedApiVersion));
        return nullptr;
    }

    auto getInstance =
        reinterpret_cast<GetInstance>(sharedLibrary.resolve("getInstance"));
    if (getInstance == nullptr)
    {
        qWarning().noquote()
            << QString("Shared Library '%1' is not a plugin")
                   .arg(fileInfo.baseName());
        return nullptr;
    }

    return getInstance();
}

int main(int argc, char** argv)
{
    std::cout << "Plugin found:" << std::endl;

    std::vector<std::unique_ptr<PluginApi>> plugins;

    QCoreApplication app{argc, argv};

    QFileInfo appFile{app.applicationFilePath()};

    auto files = listDir(appFile.dir());

    for (const auto& file : files)
    {
        qDebug() << "File: " << file;
        auto plugin = loadLibrary(file, {1, 0, 1});
        if (plugin)
        {
            plugins.emplace_back(plugin);
        }
        else
        {
            qDebug() << "Loading plugin failed: nullptr received";
        }
    }

    qDebug() << "Loaded plugins:" << plugins.size();

    for(auto& plugin : plugins) {
        qDebug().noquote() << "Plugin version:" << toString(plugin->version());
    }

    return 0;
}
