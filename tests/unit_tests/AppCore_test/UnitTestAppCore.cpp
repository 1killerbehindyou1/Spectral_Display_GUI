#include <FileManager.hpp>
#include <TransformEngine.hpp>
#include <gtest/gtest.h>

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

    const bool loaded = fileManager.loadPixMap(QUrl("https://example.com/image.png"));

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
                     [&](std::shared_ptr<QPixmap>) { ++emittedCount; });

    transformEngine.transformImage(6, 30, 2, QPoint{5, 5});

    EXPECT_EQ(emittedCount, 0);
}

TEST(TransformEngineTest, transformImageWithPixmapEmitsSignalWithPixmap)
{
    TransformEngine transformEngine;

    QImage inputImage(32, 32, QImage::Format_RGB32);
    inputImage.fill(Qt::white);
    auto pixmap = std::make_shared<QPixmap>(QPixmap::fromImage(inputImage));
    transformEngine.setPixmap(pixmap);

    int emittedCount = 0;
    std::shared_ptr<QPixmap> transformedPixmap;

    QObject::connect(&transformEngine, &TransformEngine::transformReady,
                     [&](std::shared_ptr<QPixmap> pix)
                     {
                         ++emittedCount;
                         transformedPixmap = std::move(pix);
                     });

    transformEngine.transformImage(8, 45, 2, QPoint{16, 16});

    EXPECT_EQ(emittedCount, 1);
    ASSERT_NE(transformedPixmap, nullptr);
    EXPECT_FALSE(transformedPixmap->isNull());
}

} // namespace
