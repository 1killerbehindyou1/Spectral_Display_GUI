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
    QVariantMap loadSettingsInternal(const QString& filePath,
                                     bool fallbackToDefault);
    bool saveSettingsInternal(const QString& filePath,
                              const QVariantMap& settings);
    QString localPathFromUrl(const QUrl& path);
    bool ensureProjectConfigDirectory();

    QJsonObject defaultSettingsJson() const;
    bool validateSettings(const QJsonObject& root, QString* error) const;
    bool validateControlSettings(const QJsonObject& controls,
                                 QString* error) const;
    bool validateViewSettings(const QJsonObject& view, QString* error) const;
    bool validateSelectionSettings(const QJsonObject& selection,
                                   QString* error) const;
    bool validateFilesSettings(const QJsonObject& files, QString* error) const;
    bool validateRange(const QJsonObject& object, const QString& key,
                       int minValue, int maxValue, QString* error) const;
    bool validateBool(const QJsonObject& object, const QString& key,
                      QString* error) const;
    bool validateString(const QJsonObject& object, const QString& key,
                        QString* error) const;
    void setLastError(const QString& error);
    void setProjectRootPath(const QString& path);

    QString m_last_error;
    QString m_project_root_path;
};
