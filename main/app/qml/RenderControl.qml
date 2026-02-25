import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    implicitWidth: 500
    implicitHeight: 500
    padding: 10
    background: Rectangle
    {
        color: "#c8d6e8"
    }

    contentItem: ColumnLayout
    {
        anchors.fill: parent
        spacing: 10

        GroupBox
        {
             title: "Parameters"
             font.pixelSize: 15
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop

             contentItem: ColumnLayout
             {
                spacing: 20
                Text{text: "Spectral display hardware"; font.bold: true; font.pixelSize: 18 }
                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 50
                    color: "transparent"
                    border.width: 0
                    border.color: "transparent"
                }

                Rectangle
                {
                    height: 1
                    border.width: 2
                    color: "#b1b9c5"
                    Layout.fillWidth: true
                }

                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    border.width: 0
                    border.color: "transparent"
                }
            }
        }
    }

    Component.onCompleted:
    {
    }
}




