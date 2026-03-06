/****************************************************************************
** Generated QML type registration code
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <QtQml/qqml.h>
#include <QtQml/qqmlmoduleregistration.h>

#include <piechart.h>
#include <pieslice.h>

void qml_register_types_Charts()
{
    qmlRegisterTypesAndRevisions<PieChart>("Charts", 1);
    qmlRegisterTypesAndRevisions<PieSlice>("Charts", 1);
    qmlRegisterModule("Charts", 1, 0);
}

static const QQmlModuleRegistration registration("Charts", 1, qml_register_types_Charts);
