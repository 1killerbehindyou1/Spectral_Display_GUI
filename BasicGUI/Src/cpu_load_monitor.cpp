#include "cpu_load_monitor.h"
#include <fstream>
#include <limits>

void CpuLoadMonitor::measure()
{
    m_currentJiffies = getJiffies();

    const double dWork = m_currentJiffies.work - m_previousJiffies.work;
    const double dTotal = m_currentJiffies.total - m_previousJiffies.total;

    if (dTotal == 0)
        m_cpuLoad = "-";
    else
        m_cpuLoad = QString().setNum(dWork / dTotal * 100., 'g', 2);

    m_previousJiffies = m_currentJiffies;
}

CpuLoadMonitor::Jiffies CpuLoadMonitor::getJiffies()
{
    std::ifstream stateFile("/proc/stat");
    stateFile.ignore(std::numeric_limits<std::streamsize>::max(), ' ');

    unsigned work = 0;
    unsigned total = 0;

    for (int i = 0; i < 4; ++i)
    {
        int n;
        stateFile >> n;
        total += n;
        if (i < 3)
            work += n;
    }

    return {work, total};
}
