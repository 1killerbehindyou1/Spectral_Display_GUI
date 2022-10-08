
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

    void acqistionFromFile();

    void sendDataToFile();

public slots:
    void acqusitonFromRuler();

private:

    FileManager m_file_manager;

};

#endif

