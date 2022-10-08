import QtQuick 2.0
import utility.system_telemetry 1.0

Rectangle {

    id: telemetry_block
    width: parent.implicitWidth
    height: 50

    SystemTelemetry{
        id: telemetry
        frequency: 0.5
    }

    Rectangle {
        id: telemetry_container
        color: "#a3adba"
        anchors.fill: parent
        

        Text {
            id: element
            text: qsTr("Cpu load")
            anchors.top: parent.top
            anchors.topMargin: 19
            anchors.left: parent.left
            anchors.leftMargin: 0
            font.pixelSize: 12
        }

        Text {
            id: element1
            text: telemetry.cpu_load + " %"
            anchors.top: parent.top
            anchors.topMargin: 19
            anchors.right: parent.right
            anchors.rightMargin: 0
            font.pixelSize: 12
        }

        Text {
            id: element2
            text: qsTr("RAM")
            anchors.top: parent.top
            anchors.topMargin: 38
            anchors.left: parent.left
            font.pixelSize: 12
        }

        Text {
            id: element3
            anchors.top: parent.top
            anchors.topMargin: 38
            anchors.right: parent.right
            text: telemetry.ram_used + "/" + telemetry.ram_total + " MB (" + Math.ceil(telemetry.ram_used/telemetry.ram_total * 100) + " %)"
            font.pixelSize: 12
        }
    }
    
}
