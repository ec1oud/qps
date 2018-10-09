#include "qtquick_plugin.h"
#include "processmodel.h"

#include <qqml.h>

void QtquickPlugin::registerTypes(const char *uri)
{
    // @uri org.lxqt.qps
    qmlRegisterType<ProcessModel>(uri, 1, 0, "ProcessModel");
}

