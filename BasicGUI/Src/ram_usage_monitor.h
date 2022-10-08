#ifndef RAM_USAGE_MONITOR_H_
#define RAM_USAGE_MONITOR_H_


class RamUsageMonitor
{
public:
    RamUsageMonitor()
    : m_ramTotal(getRamTotal())
    {}

    int ramTotal() const { return m_ramTotal; }

    int ramUsed() const { return m_ramUsed; }

    void measure();

private:
    static int getRamTotal();
    static int getRamFree();

    int m_ramTotal;
    int m_ramUsed = 0;
};

#endif 
