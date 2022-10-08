#include "system_telemetry.h"


SystemTelemetry::SystemTelemetry(QObject* parent) : QObject(parent)
{
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this,
            &SystemTelemetry::measurePeriodElapsed);
}

void SystemTelemetry::setFrequency(double freq)
{
    m_timer->setInterval(1000 / freq);
    if (!m_timer->isActive())
        m_timer->start();
}

double SystemTelemetry::getFrequency() const
{
    return 1000. / m_timer->interval();
}

void SystemTelemetry::measurePeriodElapsed()
{
    m_cpuMonitor.measure();
    m_ramUsageMonitor.measure();

    emit telemetryChanged();
}

