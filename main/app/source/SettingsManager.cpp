#include "SettingsManager.hpp"

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUrl>

namespace
{
constexpr int SETTINGS_VERSION = 1;
const QString kProjectFolderName = QStringLiteral("SpectralDisplayPro");
const QString kSourceImagesFolderName = QStringLiteral("image_to_transform");
const QString kTransformedImagesFolderName =
    QStringLiteral("transformed_image");
} // namespace

SettingsManager::SettingsManager(QObject* parent)
    : QObject(parent),
      m_project_root_path(QDir::cleanPath(
          QDir::currentPath() + QStringLiteral("/SpectralDisplayPro")))
{
}

QVariantMap SettingsManager::loadSettings()
{
    return loadSettingsInternal(settingsPath(), true);
}

bool SettingsManager::saveSettings(const QVariantMap& settings)
{
    return saveSettingsInternal(settingsPath(), settings);
}

QVariantMap SettingsManager::loadSettingsFromFile(const QUrl& path)
{
    const QString local_path = localPathFromUrl(path);
    if (local_path.isEmpty())
    {
        return QVariantMap{};
    }
    return loadSettingsInternal(local_path, false);
}

bool SettingsManager::saveSettingsToFile(const QUrl& path,
                                         const QVariantMap& settings)
{
    const QString local_path = localPathFromUrl(path);
    if (local_path.isEmpty())
    {
        return false;
    }
    return saveSettingsInternal(local_path, settings);
}

QVariantMap SettingsManager::defaultSettings() const
{
    return defaultSettingsJson().toVariantMap();
}

bool SettingsManager::createProject(const QUrl& parentFolderUrl)
{
    const QString parent_path = localPathFromUrl(parentFolderUrl);
    if (parent_path.isEmpty())
    {
        return false;
    }

    QDir parent_dir(parent_path);
    if (!parent_dir.exists())
    {
        setLastError(QStringLiteral("Selected parent folder does not exist."));
        return false;
    }

    const QString project_path =
        QDir::cleanPath(parent_dir.filePath(kProjectFolderName));
    QDir project_dir(project_path);
    if (!project_dir.exists() && !parent_dir.mkpath(kProjectFolderName))
    {
        setLastError(QStringLiteral("Failed to create project folder."));
        return false;
    }

    if (!project_dir.mkpath(kSourceImagesFolderName) ||
        !project_dir.mkpath(kTransformedImagesFolderName) ||
        !project_dir.mkpath(QStringLiteral(".config")))
    {
        setLastError(QStringLiteral("Failed to create project subfolders."));
        return false;
    }

    setProjectRootPath(project_path);

    const QVariantMap defaults = defaultSettings();
    if (!saveSettingsInternal(settingsPath(), defaults))
    {
        return false;
    }

    setLastError(QString{});
    return true;
}

QString SettingsManager::projectRootPath() const { return m_project_root_path; }

QString SettingsManager::projectRootUrl() const
{
    return QUrl::fromLocalFile(projectRootPath()).toString();
}

QString SettingsManager::settingsPath() const
{
    return settingsFolderPath() + QStringLiteral("/settings.json");
}

QString SettingsManager::settingsFolderPath() const
{
    return QDir::cleanPath(projectRootPath() + QStringLiteral("/.config"));
}

QString SettingsManager::settingsFolderUrl() const
{
    return QUrl::fromLocalFile(settingsFolderPath()).toString();
}

QString SettingsManager::sourceImagesFolderPath() const
{
    return QDir::cleanPath(projectRootPath() + QStringLiteral("/") +
                           kSourceImagesFolderName);
}

QString SettingsManager::sourceImagesFolderUrl() const
{
    return QUrl::fromLocalFile(sourceImagesFolderPath()).toString();
}

QString SettingsManager::transformedImagesFolderPath() const
{
    return QDir::cleanPath(projectRootPath() + QStringLiteral("/") +
                           kTransformedImagesFolderName);
}

QString SettingsManager::transformedImagesFolderUrl() const
{
    return QUrl::fromLocalFile(transformedImagesFolderPath()).toString();
}

QString SettingsManager::schemaPath() const
{
    return QStringLiteral("qrc:/json_schema/settings.schema.json");
}

QString SettingsManager::lastError() const { return m_last_error; }

QVariantMap SettingsManager::loadSettingsInternal(const QString& filePath,
                                                  bool fallbackToDefault)
{
    if (fallbackToDefault && filePath == settingsPath())
    {
        ensureProjectConfigDirectory();
    }

    QFile file(filePath);
    if (!file.exists())
    {
        if (fallbackToDefault)
        {
            const QVariantMap defaults = defaultSettings();
            saveSettingsInternal(filePath, defaults);
            setLastError(QString{});
            return defaults;
        }

        setLastError(QStringLiteral("Selected settings file does not exist."));
        return QVariantMap{};
    }

    if (!file.open(QIODevice::ReadOnly))
    {
        setLastError(
            QStringLiteral("Failed to open settings file for reading."));
        return fallbackToDefault ? defaultSettings() : QVariantMap{};
    }

    const QByteArray content = file.readAll();
    QJsonParseError parse_error{};
    const QJsonDocument json = QJsonDocument::fromJson(content, &parse_error);

    if (parse_error.error != QJsonParseError::NoError || !json.isObject())
    {
        setLastError(QStringLiteral("Invalid settings JSON format."));
        return fallbackToDefault ? defaultSettings() : QVariantMap{};
    }

    QString validation_error;
    if (!validateSettings(json.object(), &validation_error))
    {
        setLastError(validation_error);
        return fallbackToDefault ? defaultSettings() : QVariantMap{};
    }

    setLastError(QString{});
    return json.object().toVariantMap();
}

bool SettingsManager::saveSettingsInternal(const QString& filePath,
                                           const QVariantMap& settings)
{
    const QJsonObject root = QJsonObject::fromVariantMap(settings);

    QString validation_error;
    if (!validateSettings(root, &validation_error))
    {
        setLastError(validation_error);
        return false;
    }

    QFileInfo file_info(filePath);
    QDir directory = file_info.dir();
    if (!directory.exists() && !directory.mkpath(QStringLiteral(".")))
    {
        setLastError(QStringLiteral("Failed to create settings directory."));
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        setLastError(
            QStringLiteral("Failed to open settings file for writing."));
        return false;
    }

    const QJsonDocument json(root);
    file.write(json.toJson(QJsonDocument::Indented));
    setLastError(QString{});
    return true;
}

QString SettingsManager::localPathFromUrl(const QUrl& path)
{
    if (!path.isLocalFile())
    {
        setLastError(QStringLiteral("Selected path is not a local file."));
        return QString{};
    }

    const QString local_path = path.toLocalFile();
    if (local_path.isEmpty())
    {
        setLastError(QStringLiteral("Selected file path is empty."));
        return QString{};
    }

    return local_path;
}

bool SettingsManager::ensureProjectConfigDirectory()
{
    QDir directory(settingsFolderPath());
    if (directory.exists())
    {
        return true;
    }

    if (!directory.mkpath(QStringLiteral(".")))
    {
        setLastError(QStringLiteral("Failed to create settings directory."));
        return false;
    }

    return true;
}

void SettingsManager::setProjectRootPath(const QString& path)
{
    const QString normalized = QDir::cleanPath(path);
    if (normalized == m_project_root_path)
    {
        return;
    }

    m_project_root_path = normalized;
    emit projectRootPathChanged();
}

QJsonObject SettingsManager::defaultSettingsJson() const
{
    QJsonObject transform_defaults;
    transform_defaults.insert(QStringLiteral("radius"), 100);
    transform_defaults.insert(QStringLiteral("angularResolution"), 10);
    transform_defaults.insert(QStringLiteral("loadZoom"), 1);
    transform_defaults.insert(QStringLiteral("outputZoom"), 1);

    QJsonObject render_defaults;
    render_defaults.insert(QStringLiteral("ledCount"), 25);
    render_defaults.insert(QStringLiteral("ledAngle"), 5);
    render_defaults.insert(QStringLiteral("ledSize"), 5);
    render_defaults.insert(QStringLiteral("ledDistance"), 2);
    render_defaults.insert(QStringLiteral("ledRotationSpeed"), 600);

    QJsonObject controls_defaults;
    controls_defaults.insert(QStringLiteral("transform"), transform_defaults);
    controls_defaults.insert(QStringLiteral("render"), render_defaults);

    QJsonObject view_defaults;
    view_defaults.insert(QStringLiteral("showSelectedImage"), false);
    view_defaults.insert(QStringLiteral("showRenderedPreview"), false);
    view_defaults.insert(QStringLiteral("previewRotation"), 180);

    QJsonObject selection_defaults;
    selection_defaults.insert(QStringLiteral("pointX"), 0);
    selection_defaults.insert(QStringLiteral("pointY"), 0);

    QJsonObject files_defaults;
    files_defaults.insert(QStringLiteral("lastLoadedFile"), QString{});
    files_defaults.insert(QStringLiteral("lastSavedFile"), QString{});

    QJsonObject current;
    current.insert(QStringLiteral("controls"), controls_defaults);
    current.insert(QStringLiteral("view"), view_defaults);
    current.insert(QStringLiteral("selection"), selection_defaults);

    QJsonObject root;
    root.insert(QStringLiteral("$schema"), schemaPath());
    root.insert(QStringLiteral("version"), SETTINGS_VERSION);
    root.insert(QStringLiteral("defaults"), current);
    root.insert(QStringLiteral("current"), current);
    root.insert(QStringLiteral("files"), files_defaults);
    return root;
}

bool SettingsManager::validateSettings(const QJsonObject& root,
                                       QString* error) const
{
    if (!root.contains(QStringLiteral("$schema")) ||
        !root.value(QStringLiteral("$schema")).isString())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: '$schema' must be a string.");
        }
        return false;
    }

    if (!root.contains(QStringLiteral("version")) ||
        !root.value(QStringLiteral("version")).isDouble())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: 'version' must be an integer.");
        }
        return false;
    }

    const int version = root.value(QStringLiteral("version")).toInt(-1);
    if (version != SETTINGS_VERSION)
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: unsupported 'version'.");
        }
        return false;
    }

    if (!root.contains(QStringLiteral("defaults")) ||
        !root.value(QStringLiteral("defaults")).isObject())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: 'defaults' must be an object.");
        }
        return false;
    }

    if (!root.contains(QStringLiteral("current")) ||
        !root.value(QStringLiteral("current")).isObject())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: 'current' must be an object.");
        }
        return false;
    }

    if (!root.contains(QStringLiteral("files")) ||
        !root.value(QStringLiteral("files")).isObject())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral(
                "Settings validation failed: 'files' must be an object.");
        }
        return false;
    }

    const auto validate_state = [this, error](const QJsonObject& state) -> bool
    {
        if (!state.contains(QStringLiteral("controls")) ||
            !state.value(QStringLiteral("controls")).isObject())
        {
            if (error != nullptr)
            {
                *error = QStringLiteral("Settings validation failed: "
                                        "'controls' must be an object.");
            }
            return false;
        }

        if (!state.contains(QStringLiteral("view")) ||
            !state.value(QStringLiteral("view")).isObject())
        {
            if (error != nullptr)
            {
                *error = QStringLiteral(
                    "Settings validation failed: 'view' must be an object.");
            }
            return false;
        }

        if (!state.contains(QStringLiteral("selection")) ||
            !state.value(QStringLiteral("selection")).isObject())
        {
            if (error != nullptr)
            {
                *error = QStringLiteral("Settings validation failed: "
                                        "'selection' must be an object.");
            }
            return false;
        }

        if (!validateControlSettings(
                state.value(QStringLiteral("controls")).toObject(), error))
        {
            return false;
        }

        if (!validateViewSettings(
                state.value(QStringLiteral("view")).toObject(), error))
        {
            return false;
        }

        if (!validateSelectionSettings(
                state.value(QStringLiteral("selection")).toObject(), error))
        {
            return false;
        }

        return true;
    };

    if (!validate_state(root.value(QStringLiteral("defaults")).toObject()))
    {
        return false;
    }

    if (!validate_state(root.value(QStringLiteral("current")).toObject()))
    {
        return false;
    }

    return validateFilesSettings(root.value(QStringLiteral("files")).toObject(),
                                 error);
}

bool SettingsManager::validateControlSettings(const QJsonObject& controls,
                                              QString* error) const
{
    if (!controls.contains(QStringLiteral("transform")) ||
        !controls.value(QStringLiteral("transform")).isObject())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: "
                                    "'controls.transform' must be an object.");
        }
        return false;
    }

    if (!controls.contains(QStringLiteral("render")) ||
        !controls.value(QStringLiteral("render")).isObject())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: "
                                    "'controls.render' must be an object.");
        }
        return false;
    }

    const QJsonObject transform =
        controls.value(QStringLiteral("transform")).toObject();
    const QJsonObject render =
        controls.value(QStringLiteral("render")).toObject();

    return validateRange(transform, QStringLiteral("radius"), 1, 240, error) &&
           validateRange(transform, QStringLiteral("angularResolution"), 1, 360,
                         error) &&
           validateRange(transform, QStringLiteral("loadZoom"), 1, 10, error) &&
           validateRange(transform, QStringLiteral("outputZoom"), 1, 10,
                         error) &&
           validateRange(render, QStringLiteral("ledCount"), 1, 200, error) &&
           validateRange(render, QStringLiteral("ledAngle"), 1, 360, error) &&
           validateRange(render, QStringLiteral("ledSize"), 1, 360, error) &&
           validateRange(render, QStringLiteral("ledDistance"), 1, 10, error) &&
           validateRange(render, QStringLiteral("ledRotationSpeed"), 1, 6000,
                         error);
}

bool SettingsManager::validateViewSettings(const QJsonObject& view,
                                           QString* error) const
{
    return validateBool(view, QStringLiteral("showSelectedImage"), error) &&
           validateBool(view, QStringLiteral("showRenderedPreview"), error) &&
           validateRange(view, QStringLiteral("previewRotation"), 0, 359,
                         error);
}

bool SettingsManager::validateSelectionSettings(const QJsonObject& selection,
                                                QString* error) const
{
    return validateRange(selection, QStringLiteral("pointX"), 0, 100000,
                         error) &&
           validateRange(selection, QStringLiteral("pointY"), 0, 100000, error);
}

bool SettingsManager::validateFilesSettings(const QJsonObject& files,
                                            QString* error) const
{
    return validateString(files, QStringLiteral("lastLoadedFile"), error) &&
           validateString(files, QStringLiteral("lastSavedFile"), error);
}

bool SettingsManager::validateRange(const QJsonObject& object,
                                    const QString& key, int minValue,
                                    int maxValue, QString* error) const
{
    if (!object.contains(key) || !object.value(key).isDouble())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: '") + key +
                     QStringLiteral("' must be an integer.");
        }
        return false;
    }

    const int value = object.value(key).toInt();
    if (value < minValue || value > maxValue)
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: '") + key +
                     QStringLiteral("' is out of allowed range.");
        }
        return false;
    }

    return true;
}

bool SettingsManager::validateBool(const QJsonObject& object,
                                   const QString& key, QString* error) const
{
    if (!object.contains(key) || !object.value(key).isBool())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: '") + key +
                     QStringLiteral("' must be boolean.");
        }
        return false;
    }
    return true;
}

bool SettingsManager::validateString(const QJsonObject& object,
                                     const QString& key, QString* error) const
{
    if (!object.contains(key) || !object.value(key).isString())
    {
        if (error != nullptr)
        {
            *error = QStringLiteral("Settings validation failed: '") + key +
                     QStringLiteral("' must be string.");
        }
        return false;
    }
    return true;
}

void SettingsManager::setLastError(const QString& error)
{
    if (m_last_error == error)
    {
        return;
    }

    m_last_error = error;
    emit lastErrorChanged();
}
