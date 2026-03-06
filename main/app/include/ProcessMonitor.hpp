#pragma once

#include <QObject>

/**
 * @brief Provides process CPU and RAM metrics for QML UI.
 */
class ProcessMonitor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cpuPercent READ cpuPercent NOTIFY metricsChanged)
    Q_PROPERTY(double ramMb READ ramMb NOTIFY metricsChanged)

public:
    /**
     * @brief Constructs process monitor.
     * @param parent Optional QObject parent.
     */
    explicit ProcessMonitor(QObject* parent = nullptr);

    /** @brief Returns latest CPU usage percent. */
    double cpuPercent() const;
    /** @brief Returns latest resident RAM usage in MB. */
    double ramMb() const;

    /** @brief Refreshes CPU and RAM metrics from /proc. */
    Q_INVOKABLE void refresh();

signals:
    /** @brief Emitted when metrics are refreshed. */
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
