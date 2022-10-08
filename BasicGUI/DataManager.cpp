
#include "DataManager.h"
#include "LedRuler.h"
#include <iostream>

DataManager::DataManager(QObject* parent) : QObject(parent){

}

void DataManager::acqistionFromFile(){

}

void  DataManager::acqusitonFromRuler(){
  
  std::cout<< "wielkosc wektora:  "  << LedRuler::m_projection->size() << std::endl;
}

void  DataManager::sendDataToFile()
{
     m_file_manager.saveToFile();
}

