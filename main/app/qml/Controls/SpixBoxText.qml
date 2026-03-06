import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls

Controls.TextField
{
    id: textInp
    property int currentValue: 0
    property int minValue: 0
    property int maxValue: 0
    z: 2
    text: currentValue
    color: "#243956"
    horizontalAlignment: Qt.AlignHCenter
    verticalAlignment: Qt.AlignVCenter
    font.bold: true
    font.pixelSize: 20
    activeFocusOnTab: true
    validator: IntValidator
    {
        bottom: minValue
        top: maxValue
    }

    inputMethodHints: Qt.ImhFormattedNumbersOnly
    background: Rectangle
    {
        color: "transparent"
    }
}
