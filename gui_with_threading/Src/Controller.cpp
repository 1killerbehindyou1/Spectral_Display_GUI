#include "Controller.h"

#include <QDebug>

Controller::Controller() : QObject() {}

void Controller::startViaThreadObject()
{
    emit newLog("Via thread object called");
}

void Controller::startViaSignals() { emit newLog("Via signals called"); }
