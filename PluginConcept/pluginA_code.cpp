#include "plugin_api.h"

class PluginA : public PluginApi
{
    Version version() override { return {2, 0, 5}; }
};

extern "C"
{
    __declspec(dllexport) Version pluginApiVersion() { return {1, 0, 2}; }

    __declspec(dllexport) PluginApi* getInstance() { return new PluginA; }
}
