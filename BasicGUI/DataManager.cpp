
#include "DataManager.h"
#include "LedRuler.h"
#include <iostream>

DataManager::DataManager(QObject* parent) : QObject(parent){

}

void DataManager::loadFromFile(){

}

void  DataManager::sendDataToFile()
{
     m_file_manager.saveToFile();
}

QVector<QVector<QColor>>* DataManager::m_projection = nullptr;