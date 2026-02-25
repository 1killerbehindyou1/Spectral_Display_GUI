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
        return led.onParameterChanged(num, angle, size);
    }
    function setPixmap()
    {
        led.pixmap = file_manager.pixmap_pointer
    }

    function checkRenderedPreview(state: bool)
    {
        return led.showOutputPreview(state);
    }

    function updatePoint(mouseX: real, mouseY: real)
    {
        return led.setPoint(Qt.point(mouseX, mouseY));
    }

    function getOutImage()
    {
        return led.getRenderedImage();
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