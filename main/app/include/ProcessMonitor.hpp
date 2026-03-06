#pragma once

#include <QObject>

class ProcessMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cpuPercent READ cpuPercent NOTIFY metricsChanged)
    Q_PROPERTY(double ramMb READ ramMb NOTIFY metricsChanged)

public:
    explicit ProcessMonitor(QObject* parent = nullptr);

    double cpuPercent() const;
    double ramMb() const;

    Q_INVOKABLE void refresh();

signals:
    void metricsChanged();

private:
    static quint64 readTotalCpuJiffies();
    static quint64 readProcessCpuJiffies();
    static double readResidentRamMb();

    quint64 m_prevTotalCpuJiffies{0};
    quint64 m_prevProcessCpuJiffies{0};
    double m_cpuPercent{0.0};
    double m_ramMb{0.0};
    bool m_hasCpuBaseline{false};
};
