#include "ram_usage_monitor.h"
#include <fstream>
#include <limits>


constexpr auto mem_info_file_path = "/proc/meminfo";

constexpr int kb_to_mb(int kilobytes)
{
    return kilobytes / 1024;
}

int RamUsageMonitor::getRamTotal()
{
    int ramTotal;
    std::ifstream memInfo(mem_info_file_path);
    memInfo.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    memInfo >> ramTotal;
    return kb_to_mb(ramTotal);
}

int RamUsageMonitor::getRamFree()
{
    std::ifstream memInfo(mem_info_file_path);
    int free = 0;

    for (int i = 0; i < 2; ++i)
    {
        memInfo.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        memInfo.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }

    memInfo >> free;
    return kb_to_mb(free);
}

void RamUsageMonitor::measure()
{
    m_ramUsed = m_ramTotal - getRamFree();
}