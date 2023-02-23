#ifndef PLUGIN_FUNTIONS_H_
#define PLUGIN_FUNTIONS_H_

#include <cstdint>

#include "plugin_api.h"

extern "C"
{
    Version pluginApiVersion();

    PluginApi* getInstance();
}

using GetApiVersion = Version (*)();
using GetInstance = PluginApi* (*)();

#endif // PLUGIN_FUNTIONS_H_
