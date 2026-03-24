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
    /** @brief Reads total CPU jiffies from system statistics. */
    static quint64 readTotalCpuJiffies();
    /** @brief Reads current process CPU jiffies from procfs. */
    static quint64 readProcessCpuJiffies();
    /** @brief Reads resident process memory usage in MB. */
    static double readResidentRamMb();

    /** @brief Previously sampled total CPU jiffies. */
    quint64 m_prevTotalCpuJiffies{0};
    /** @brief Previously sampled process CPU jiffies. */
    quint64 m_prevProcessCpuJiffies{0};
    /** @brief Last computed CPU utilization percentage. */
    double m_cpuPercent{0.0};
    /** @brief Last computed resident memory usage in MB. */
    double m_ramMb{0.0};
    /** @brief Indicates whether initial CPU baseline was captured. */
    bool m_hasCpuBaseline{false};
};
