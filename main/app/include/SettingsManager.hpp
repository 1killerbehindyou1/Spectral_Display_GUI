#pragma once

#include <QObject>
#include <QVariantMap>

class QJsonObject;
class QUrl;

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
    explicit SettingsManager(QObject* parent = nullptr);

    Q_INVOKABLE QVariantMap loadSettings();
    Q_INVOKABLE bool saveSettings(const QVariantMap& settings);
    Q_INVOKABLE QVariantMap loadSettingsFromFile(const QUrl& path);
    Q_INVOKABLE bool saveSettingsToFile(const QUrl& path,
                                        const QVariantMap& settings);
    Q_INVOKABLE QVariantMap defaultSettings() const;
    Q_INVOKABLE bool createProject(const QUrl& parentFolderUrl);

    QString projectRootPath() const;
    QString projectRootUrl() const;
    QString settingsPath() const;
    QString settingsFolderPath() const;
    QString settingsFolderUrl() const;
    QString sourceImagesFolderPath() const;
    QString sourceImagesFolderUrl() const;
    QString transformedImagesFolderPath() const;
    QString transformedImagesFolderUrl() const;
    QString schemaPath() const;
    QString lastError() const;

signals:
    void lastErrorChanged();
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
