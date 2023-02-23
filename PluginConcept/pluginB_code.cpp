#include "plugin_api.h"

class PluginB : public PluginApi
{
    Version version() override { return {1, 4, 2}; }
};

extern "C"
{
    __declspec(dllexport) Version pluginApiVersion() { return {1, 0, 1}; }

    __declspec(dllexport) PluginApi* getInstance() { return new PluginB; }
}
