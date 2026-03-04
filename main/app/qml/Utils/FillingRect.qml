import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Control
{
    id: root
    property int fillerHeight: 10
    implicitHeight: fillerHeight
    implicitWidth: 1

    contentItem: Rectangle
    {
        anchors.fill: parent
        color: "transparent"
        border.width: 0
        border.color: "transparent"
    }
}