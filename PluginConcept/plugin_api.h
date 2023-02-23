#ifndef PLUGIN_API_H_
#define PLUGIN_API_H_

#include <cstdint>

struct Version
{
    uint32_t major, minor, release;
};

struct PluginApi
{
    virtual Version version() = 0;
};

#endif // PLUGIN_API_H_