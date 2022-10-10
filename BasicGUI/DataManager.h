
#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include <QObject>
#include <QColor>
#include "FileManager.h"
#include <QVector>

class DataManager : public QObject{

    Q_OBJECT

public:
    DataManager(QObject *parent =0);

    void loadFromFile();
    void sendDataToFile();

    static QVector<QVector<QColor>>* m_projection;

private:
    FileManager m_file_manager;
    
};

#endif

