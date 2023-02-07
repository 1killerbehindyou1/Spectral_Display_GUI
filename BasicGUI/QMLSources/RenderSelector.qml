import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    function selectorParameterChanged(l_size: int, number_of_leds: int)
    {
        return selector_local.selectorUpdate(number_of_leds, l_size);
    }

    id: root
    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }

    Selector
    {
        id: selector_local
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked: selector_local.setPoint(Qt.point(mouseX, mouseY))
        }
    }
}
