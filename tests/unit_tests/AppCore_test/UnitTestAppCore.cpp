#include <FileManager.hpp>
#include <SettingsManager.hpp>
#include <TransformEngine.hpp>
#include <gtest/gtest.h>

#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QTemporaryDir>
#include <QUrl>

namespace
{

TEST(FileManagerTest, loadPixMapRejectsNonLocalUrl)
{
    FileManager fileManager;

    int errorCount = 0;
    QString errorTitle;
    QString errorMessage;

    QObject::connect(&fileManager, &FileManager::fileErrLoad,
                     [&](QString title, QString message)
                     {
                         ++errorCount;
                         errorTitle = std::move(title);
                         errorMessage = std::move(message);
                     });

    const bool loaded =
        fileManager.loadPixMap(QUrl("https://example.com/image.png"));

    EXPECT_FALSE(loaded);
    EXPECT_EQ(errorCount, 1);
    EXPECT_EQ(errorTitle, "Loaded file failed");
    EXPECT_FALSE(errorMessage.isEmpty());
}

TEST(FileManagerTest, loadPixMapLoadsValidLocalImageAndEmitsSignals)
{
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    const QString inputPath = tempDir.path() + "/input.png";
    QImage inputImage(8, 8, QImage::Format_RGB32);
    inputImage.fill(Qt::red);
    ASSERT_TRUE(inputImage.save(inputPath));

    FileManager fileManager;
    int imageReadyCount = 0;
    int transformReadyCount = 0;
    QPixmap emittedPixmap;

    QObject::connect(&fileManager, &FileManager::setImageOnGui,
                     [&]() { ++imageReadyCount; });
    QObject::connect(&fileManager, &FileManager::fileReadyToTransform,
                     [&](QPixmap pixmap)
                     {
                         ++transformReadyCount;
                         emittedPixmap = std::move(pixmap);
                     });

    const bool loaded = fileManager.loadPixMap(QUrl::fromLocalFile(inputPath));

    ASSERT_TRUE(loaded);
    EXPECT_EQ(imageReadyCount, 1);
    EXPECT_EQ(transformReadyCount, 1);
    ASSERT_NE(fileManager.getPixmapPointer(), nullptr);
    EXPECT_FALSE(fileManager.getPixmapPointer()->isNull());
    EXPECT_FALSE(emittedPixmap.isNull());
}

TEST(FileManagerTest, savePixMapSavesImageToDisk)
{
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    const QString outputPath = tempDir.path() + "/output.png";
    QImage outputImage(4, 4, QImage::Format_RGB32);
    outputImage.fill(Qt::green);

    FileManager fileManager;
    fileManager.savePixMap(QUrl::fromLocalFile(outputPath), &outputImage);

    EXPECT_TRUE(QFileInfo::exists(outputPath));

    QImage loadedImage;
    ASSERT_TRUE(loadedImage.load(outputPath));
    EXPECT_EQ(loadedImage.size(), outputImage.size());
}

TEST(TransformEngineTest, transformImageWithoutPixmapDoesNotEmitSignal)
{
    TransformEngine transformEngine;
    int emittedCount = 0;

    QObject::connect(&transformEngine, &TransformEngine::transformReady,
                     [&](std::shared_ptr<QImage>) { ++emittedCount; });

    transformEngine.updateNoOfPixels(30);
    transformEngine.updateAngularResolution(6);
    transformEngine.updatePoint(QPoint{5, 5});

    EXPECT_EQ(emittedCount, 0);
}

TEST(TransformEngineTest, transformImageWithPixmapEmitsSignalWithImage)
{
    TransformEngine transformEngine;

    QImage inputImage(32, 32, QImage::Format_RGB32);
    inputImage.fill(Qt::white);
    auto pixmap = std::make_shared<QPixmap>(QPixmap::fromImage(inputImage));
    transformEngine.setPixmap(pixmap);

    int emittedCount = 0;
    std::shared_ptr<QImage> transformedImage;

    QObject::connect(&transformEngine, &TransformEngine::transformReady,
                     [&](std::shared_ptr<QImage> image)
                     {
                         ++emittedCount;
                         transformedImage = std::move(image);
                     });

    transformEngine.updateNoOfPixels(45);
    transformEngine.updateAngularResolution(8);
    transformEngine.updatePoint(QPoint{16, 16});

    EXPECT_EQ(emittedCount, 1);
    ASSERT_NE(transformedImage, nullptr);
    EXPECT_FALSE(transformedImage->isNull());
}

TEST(IntegrationFlowTest, loadTransformAndSaveProducesOutputFile)
{
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    const QString inputPath = tempDir.path() + "/input.png";
    const QString outputBasePath = tempDir.path() + "/transformed_output";

    QImage inputImage(64, 64, QImage::Format_RGB32);
    inputImage.fill(Qt::blue);
    ASSERT_TRUE(inputImage.save(inputPath));

    FileManager fileManager;
    TransformEngine transformEngine;

    QObject::connect(&fileManager, &FileManager::fileReadyToTransform,
                     [&](QPixmap pixmap) {
                         transformEngine.setPixmap(
                             std::make_shared<QPixmap>(std::move(pixmap)));
                     });

    std::shared_ptr<QImage> transformedImage;
    QObject::connect(&transformEngine, &TransformEngine::transformReady,
                     [&](std::shared_ptr<QImage> image)
                     { transformedImage = std::move(image); });

    ASSERT_TRUE(fileManager.loadPixMap(QUrl::fromLocalFile(inputPath)));

    transformEngine.updateNoOfPixels(45);
    transformEngine.updateAngularResolution(8);
    transformEngine.updatePoint(QPoint{32, 32});

    ASSERT_NE(transformedImage, nullptr);
    ASSERT_FALSE(transformedImage->isNull());

    fileManager.savePixMap(QUrl::fromLocalFile(outputBasePath),
                           transformedImage.get());

    const QString outputPath = outputBasePath + ".png";
    EXPECT_TRUE(QFileInfo::exists(outputPath));

    QImage loadedOutput;
    ASSERT_TRUE(loadedOutput.load(outputPath));
    EXPECT_FALSE(loadedOutput.isNull());
}

TEST(SettingsManagerTest, saveAndLoadSettingsFromFileRoundTrip)
{
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    const QString settingsPath = tempDir.path() + "/valid_settings.json";
    const QUrl settingsUrl = QUrl::fromLocalFile(settingsPath);

    SettingsManager settingsManager;
    QVariantMap settings = settingsManager.defaultSettings();

    QVariantMap current = settings.value("current").toMap();
    QVariantMap controls = current.value("controls").toMap();
    QVariantMap render = controls.value("render").toMap();
    render.insert("ledCount", 42);
    controls.insert("render", render);
    current.insert("controls", controls);
    settings.insert("current", current);

    ASSERT_TRUE(settingsManager.saveSettingsToFile(settingsUrl, settings));
    ASSERT_TRUE(settingsManager.lastError().isEmpty());

    const QVariantMap loaded =
        settingsManager.loadSettingsFromFile(settingsUrl);
    ASSERT_TRUE(settingsManager.lastError().isEmpty());

    const int loadedLedCount = loaded.value("current")
                                   .toMap()
                                   .value("controls")
                                   .toMap()
                                   .value("render")
                                   .toMap()
                                   .value("ledCount")
                                   .toInt();
    EXPECT_EQ(loadedLedCount, 42);
}

TEST(SettingsManagerTest, loadSettingsFromFileRejectsInvalidSchemaValue)
{
    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    const QString settingsPath = tempDir.path() + "/invalid_settings.json";
    QFile file(settingsPath);
    ASSERT_TRUE(file.open(QIODevice::WriteOnly | QIODevice::Truncate));

    const QByteArray invalidJson = R"JSON(
{
    "$schema": "qrc:/json_schema/settings.schema.json",
    "version": 1,
    "defaults": {
        "controls": {
            "transform": {"radius": 100, "angularResolution": 10, "loadZoom": 1, "outputZoom": 1},
            "render": {"ledCount": 25, "ledAngle": 5, "ledSize": 5, "ledDistance": 2}
        },
        "view": {"showSelectedImage": false, "showRenderedPreview": false, "previewRotation": 180},
        "selection": {"pointX": 0, "pointY": 0}
    },
    "current": {
        "controls": {
            "transform": {"radius": 100, "angularResolution": 10, "loadZoom": 1, "outputZoom": 1},
            "render": {"ledCount": 999, "ledAngle": 5, "ledSize": 5, "ledDistance": 2}
        },
        "view": {"showSelectedImage": false, "showRenderedPreview": false, "previewRotation": 180},
        "selection": {"pointX": 0, "pointY": 0}
    },
    "files": {"lastLoadedFile": "", "lastSavedFile": ""}
}
)JSON";

    file.write(invalidJson);
    file.close();

    SettingsManager settingsManager;
    const QVariantMap loaded =
        settingsManager.loadSettingsFromFile(QUrl::fromLocalFile(settingsPath));

    EXPECT_TRUE(loaded.isEmpty());
    EXPECT_FALSE(settingsManager.lastError().isEmpty());
}

} // namespace
