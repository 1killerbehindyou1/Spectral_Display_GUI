#ifndef PLUGIN_API_HELPERS_H_
#define PLUGIN_API_HELPERS_H_

#include "plugin_api.h"
#include <utility>

QString toString(const Version& ver)
{
    return QString("%1.%2.%3").arg(ver.major).arg(ver.minor).arg(ver.release);
}

auto make_tie(const Version& ver)
{
    return std::tie(ver.major, ver.minor, ver.release);
}

bool operator==(const Version& ver1, const Version& ver2)
{
    return make_tie(ver1) == make_tie(ver2);
}

bool operator!=(const Version& ver1, const Version& ver2)
{
    return !(ver1 == ver2);
}

#endif // PLUGIN_API_HELPERS_H_
