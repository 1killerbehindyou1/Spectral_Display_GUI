#pragma once

#include <QObject>
#include <QVariantMap>

class QJsonObject;
class QUrl;

/**
 * @brief Manages application settings, validation and project folder lifecycle.
 */
class SettingsManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString projectRootPath READ projectRootPath NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(QString projectRootUrl READ projectRootUrl NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(
        QString settingsPath READ settingsPath NOTIFY projectRootPathChanged)
    Q_PROPERTY(QString settingsFolderPath READ settingsFolderPath NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(QString settingsFolderUrl READ settingsFolderUrl NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(QString sourceImagesFolderPath READ sourceImagesFolderPath NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(QString sourceImagesFolderUrl READ sourceImagesFolderUrl NOTIFY
                   projectRootPathChanged)
    Q_PROPERTY(QString transformedImagesFolderPath READ
                   transformedImagesFolderPath NOTIFY projectRootPathChanged)
    Q_PROPERTY(QString transformedImagesFolderUrl READ
                   transformedImagesFolderUrl NOTIFY projectRootPathChanged)
    Q_PROPERTY(QString schemaPath READ schemaPath CONSTANT)
    Q_PROPERTY(QString lastError READ lastError NOTIFY lastErrorChanged)

public:
    /**
     * @brief Constructs settings manager.
     * @param parent Optional QObject parent.
     */
    explicit SettingsManager(QObject* parent = nullptr);

    /** @brief Loads settings from default project settings file. */
    Q_INVOKABLE QVariantMap loadSettings();
    /**
     * @brief Saves settings to default project settings file.
     * @param settings Settings payload.
     * @return true on success, false otherwise.
     */
    Q_INVOKABLE bool saveSettings(const QVariantMap& settings);
    /**
     * @brief Loads settings from selected file URL.
     * @param path Source settings file URL.
     * @return Loaded settings map or empty map on failure.
     */
    Q_INVOKABLE QVariantMap loadSettingsFromFile(const QUrl& path);
    /**
     * @brief Saves settings to selected file URL.
     * @param path Destination settings file URL.
     * @param settings Settings payload.
     * @return true on success, false otherwise.
     */
    Q_INVOKABLE bool saveSettingsToFile(const QUrl& path,
                                        const QVariantMap& settings);
    /** @brief Returns default settings payload. */
    Q_INVOKABLE QVariantMap defaultSettings() const;
    /**
     * @brief Creates project folder structure and initializes settings file.
     * @param parentFolderUrl Parent folder URL where project will be created.
     * @return true on success, false otherwise.
     */
    Q_INVOKABLE bool createProject(const QUrl& parentFolderUrl);

    /** @brief Returns current project root path. */
    QString projectRootPath() const;
    /** @brief Returns current project root as file URL string. */
    QString projectRootUrl() const;
    /** @brief Returns full path to project settings file. */
    QString settingsPath() const;
    /** @brief Returns path to project settings directory. */
    QString settingsFolderPath() const;
    /** @brief Returns settings directory as file URL string. */
    QString settingsFolderUrl() const;
    /** @brief Returns source images folder path. */
    QString sourceImagesFolderPath() const;
    /** @brief Returns source images folder as file URL string. */
    QString sourceImagesFolderUrl() const;
    /** @brief Returns transformed images folder path. */
    QString transformedImagesFolderPath() const;
    /** @brief Returns transformed images folder as file URL string. */
    QString transformedImagesFolderUrl() const;
    /** @brief Returns JSON schema path used for settings validation. */
    QString schemaPath() const;
    /** @brief Returns last settings error message. */
    QString lastError() const;

signals:
    /** @brief Emitted when last error message changes. */
    void lastErrorChanged();
    /** @brief Emitted when project root path changes. */
    void projectRootPathChanged();

private:
    /**
     * @brief Loads settings from disk and optionally falls back to defaults.
     * @param filePath Local settings file path.
     * @param fallbackToDefault Whether to return defaults on failure.
     * @return Loaded settings map.
     */
    QVariantMap loadSettingsInternal(const QString& filePath,
                                     bool fallbackToDefault);
    /**
     * @brief Persists settings payload to disk.
     * @param filePath Local destination file path.
     * @param settings Settings payload.
     * @return true on success, false otherwise.
     */
    bool saveSettingsInternal(const QString& filePath,
                              const QVariantMap& settings);
    /**
     * @brief Converts file URL to normalized local path.
     * @param path Source URL.
     * @return Normalized local path.
     */
    QString localPathFromUrl(const QUrl& path);
    /**
     * @brief Ensures settings directory exists for current project.
     * @return true if directory is ready, false otherwise.
     */
    bool ensureProjectConfigDirectory();

    /** @brief Builds default settings JSON object used by serializer. */
    QJsonObject defaultSettingsJson() const;
    /**
     * @brief Validates full settings JSON structure.
     * @param root Settings root object.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateSettings(const QJsonObject& root, QString* error) const;
    /**
     * @brief Validates "controls" section.
     * @param controls Controls object.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateControlSettings(const QJsonObject& controls,
                                 QString* error) const;
    /**
     * @brief Validates "view" section.
     * @param view View object.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateViewSettings(const QJsonObject& view, QString* error) const;
    /**
     * @brief Validates "selection" section.
     * @param selection Selection object.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateSelectionSettings(const QJsonObject& selection,
                                   QString* error) const;
    /**
     * @brief Validates "files" section.
     * @param files Files object.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateFilesSettings(const QJsonObject& files, QString* error) const;
    /**
     * @brief Validates integer key against expected range.
     * @param object Source JSON object.
     * @param key Key name to validate.
     * @param minValue Accepted minimum value.
     * @param maxValue Accepted maximum value.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateRange(const QJsonObject& object, const QString& key,
                       int minValue, int maxValue, QString* error) const;
    /**
     * @brief Validates boolean key.
     * @param object Source JSON object.
     * @param key Key name to validate.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateBool(const QJsonObject& object, const QString& key,
                      QString* error) const;
    /**
     * @brief Validates string key.
     * @param object Source JSON object.
     * @param key Key name to validate.
     * @param error Output validation error.
     * @return true when valid, false otherwise.
     */
    bool validateString(const QJsonObject& object, const QString& key,
                        QString* error) const;
    /**
     * @brief Updates last error string and notifies observers.
     * @param error New error message.
     */
    void setLastError(const QString& error);
    /**
     * @brief Updates project root path and emits change notification.
     * @param path New project root path.
     */
    void setProjectRootPath(const QString& path);

    /** @brief Last settings or filesystem error message. */
    QString m_last_error;
    /** @brief Current project root path on local filesystem. */
    QString m_project_root_path;
};
