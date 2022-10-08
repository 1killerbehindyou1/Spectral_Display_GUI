#ifndef SYSTEM_TELEMETRY_H_
#define SYSTEM_TELEMETRY_H_

#include <QObject>
#include <QTimer>

#include "cpu_load_monitor.h"
#include "ram_usage_monitor.h"
#include <QVariant>


class SystemTelemetry : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariant cpu_load READ cpuLoad NOTIFY telemetryChanged)
    Q_PROPERTY(QVariant ram_total READ ramTotal CONSTANT)
    Q_PROPERTY(QVariant ram_used READ ramUsed NOTIFY telemetryChanged)
    Q_PROPERTY(double frequency READ getFrequency WRITE setFrequency)

public:
    
    SystemTelemetry(QObject* parent = nullptr);

    QVariant cpuLoad() const { return m_cpuMonitor.cpuLoad(); }

    QVariant ramTotal() const { return m_ramUsageMonitor.ramTotal(); }

    QVariant ramUsed() const { return m_ramUsageMonitor.ramUsed(); }

    void setFrequency(double freq);

    double getFrequency() const;

public slots:

signals:
    void telemetryChanged();

private slots:
    void measurePeriodElapsed();

private:
    QTimer* m_timer;
    CpuLoadMonitor m_cpuMonitor;
    RamUsageMonitor m_ramUsageMonitor;
};

#endif 