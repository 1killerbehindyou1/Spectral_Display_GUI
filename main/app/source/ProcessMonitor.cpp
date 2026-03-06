#include "ProcessMonitor.hpp"

#include <QFile>
#include <QRegularExpression>
#include <QStringList>
#include <QThread>

ProcessMonitor::ProcessMonitor(QObject* parent)
    : QObject(parent)
{
}

double ProcessMonitor::cpuPercent() const
{
    return m_cpuPercent;
}

double ProcessMonitor::ramMb() const
{
    return m_ramMb;
}

void ProcessMonitor::refresh()
{
    const quint64 totalCpuJiffies = readTotalCpuJiffies();
    const quint64 processCpuJiffies = readProcessCpuJiffies();

    if (!m_hasCpuBaseline)
    {
        m_prevTotalCpuJiffies = totalCpuJiffies;
        m_prevProcessCpuJiffies = processCpuJiffies;
        m_hasCpuBaseline = true;
    }
    else
    {
        const quint64 totalDelta = totalCpuJiffies - m_prevTotalCpuJiffies;
        const quint64 processDelta = processCpuJiffies - m_prevProcessCpuJiffies;

        if (totalDelta > 0)
        {
            const int threadCount = qMax(1, QThread::idealThreadCount());
            const double usage = (static_cast<double>(processDelta) / static_cast<double>(totalDelta)) * 100.0 * threadCount;
            m_cpuPercent = qBound(0.0, usage, 100.0 * threadCount);
        }

        m_prevTotalCpuJiffies = totalCpuJiffies;
        m_prevProcessCpuJiffies = processCpuJiffies;
    }

    m_ramMb = readResidentRamMb();
    emit metricsChanged();
}

quint64 ProcessMonitor::readTotalCpuJiffies()
{
    QFile file(QStringLiteral("/proc/stat"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    const QByteArray firstLine = file.readLine();
    const QList<QByteArray> tokens = firstLine.simplified().split(' ');
    if (tokens.size() < 2 || tokens.first() != "cpu")
    {
        return 0;
    }

    quint64 total = 0;
    for (int index = 1; index < tokens.size(); ++index)
    {
        total += tokens[index].toULongLong();
    }
    return total;
}

quint64 ProcessMonitor::readProcessCpuJiffies()
{
    QFile file(QStringLiteral("/proc/self/stat"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0;
    }

    const QByteArray line = file.readAll().trimmed();
    const int closingParenthesis = line.lastIndexOf(')');
    if (closingParenthesis < 0 || closingParenthesis + 1 >= line.size())
    {
        return 0;
    }

    const QByteArray tail = line.mid(closingParenthesis + 1).trimmed();
    const QList<QByteArray> fields = tail.split(' ');
    if (fields.size() <= 12)
    {
        return 0;
    }

    const quint64 utime = fields[11].toULongLong();
    const quint64 stime = fields[12].toULongLong();
    return utime + stime;
}

double ProcessMonitor::readResidentRamMb()
{
    QFile file(QStringLiteral("/proc/self/status"));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return 0.0;
    }

    while (!file.atEnd())
    {
        const QString line = QString::fromUtf8(file.readLine());
        if (line.startsWith(QStringLiteral("VmRSS:")))
        {
            const QStringList parts = line.simplified().split(' ');
            if (parts.size() >= 2)
            {
                const double rssKb = parts[1].toDouble();
                return rssKb / 1024.0;
            }
            break;
        }
    }

    return 0.0;
}
