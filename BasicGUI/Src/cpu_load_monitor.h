#ifndef CPU_LOAD_MONITOR_H_
#define CPU_LOAD_MONITOR_H_

#include <QString>

class CpuLoadMonitor
{
public:
   
    QString cpuLoad() const { return m_cpuLoad; }

    void measure();

private:
    QString m_cpuLoad = "-";

    struct Jiffies
    {
        unsigned work = 0;
        unsigned total = 0;
    };

    Jiffies m_currentJiffies;
    Jiffies m_previousJiffies;

    static Jiffies getJiffies();
};

#endif 
