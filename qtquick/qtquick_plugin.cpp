#include "qtquick_plugin.h"
#include "processmodel.h"
#include "sortfilterprocessmodel.h"

#include <qqml.h>

void QtquickPlugin::registerTypes(const char *uri)
{
    // @uri org.lxqt.qps
    qmlRegisterType<ProcessModel>(uri, 1, 0, "ProcessModel");
    qmlRegisterType<SortFilterProcessModel>(uri, 1, 0, "SortFilterProcessModel");
}

