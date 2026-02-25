import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root

    function updateLedParameters(size: int, angle: int, num: int)
    {
        console.log("line: 15 , file: RenderPanel.qml " + "size: " + size + ", angle: " + angle + ", number_of_leds: " + num);
        return led.onParameterChanged(num, angle, size);
    }
    function setPixmap()
    {
        console.log("line: 20 , file: RenderPanel.qml " + "setting pixmap");
        led.pixmap = file_manager.pixmap_pointer
    }

    function checkRenderedPreview(state: bool)
    {
        console.log("line: 25 , file: RenderPanel.qml " + "state: " + state);
        return led.showOutputPreview(state);
    }

    function updatePoint(mouseX: real, mouseY: real)
    {
        console.log("line: 28 , file: RenderPanel.qml " + "x: " + mouseX + ", y: " + mouseY);
        return led.setPoint(Qt.point(mouseX, mouseY));
    }

    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }

    contentItem: LedRuler
    {
        id: led
        anchors.fill: parent
    }
}