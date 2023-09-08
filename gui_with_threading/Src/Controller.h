#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <QObject>
#include <qobjectdefs.h>

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller();

    Q_INVOKABLE void startViaThreadObject();
    Q_INVOKABLE void startViaSignals();

signals:
    void newLog(QString msg);
};

#endif // CONTROLLER_H_