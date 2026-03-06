import QtQuick 2.15

Rectangle
{
    id: root
    property string text: ""
    property int textPixelSize: 20

    radius: 8
    implicitWidth: 40
    color: "#7799c6"

    Text
    {
        text: root.text
        color: "#243956"
        font.bold: true
        font.pixelSize: root.textPixelSize
        anchors.fill: parent
        fontSizeMode: Text.Fit
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
    }
}