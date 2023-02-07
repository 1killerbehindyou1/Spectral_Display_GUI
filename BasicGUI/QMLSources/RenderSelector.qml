import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    signal pointUpdate(real xPosition, real yPosition)

    function selectorParameterChanged(l_size: int, angle: int, number_of_leds: int)
    {
        return selector_local.selectorUpdate(number_of_leds, l_size);
    }

    property alias img_visible: loaded_image.visible
    property alias img_source:  loaded_image.source

    id: root
    implicitWidth: 720
    implicitHeight: 500

    background: Image
    {
        anchors.fill: parents
        id: loaded_image
        visible: false
        fillMode: Image.PreserveAspectFit
    }
    Selector
    {
        id: selector_local
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                selector_local.setPoint(Qt.point(mouseX, mouseY));
                root.pointUpdate(mouseX, mouseY);
            }
        }
    }
}
