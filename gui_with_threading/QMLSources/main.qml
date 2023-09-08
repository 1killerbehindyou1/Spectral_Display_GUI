import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
// import Main 1.0

ApplicationWindow 
{
    id: root
    width: 900
    height: 600
    visible: true
    title: qsTr("Threaded Gui")
    color: "lightgrey"

    ListModel{
        id: logModel
    }

    // Label {
    //     anchors.left: outputArea.left
    //     anchors.top: outputArea.top
    //     text: "<Application output>"
    //     color: "gray"
    //     visible: !logModel.count
    // }

    RowLayout
    {
        anchors.fill: parent

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            Control {
                contentItem: ColumnLayout{
                    id: outputArea
                    anchors.left: parent.left
                    anchors.right: parent.right

                    Repeater {
                        Layout.fillWidth: true
                        model: logModel
                        delegate: Label {
                            text: msg
                        }
                    }

                    Layout.fillWidth: true
                    Layout.fillHeight: true
                }
            }

            background: Rectangle {
                anchors.fill: parent
                color: "white"
            }
        }

        
        ColumnLayout {
            Layout.fillHeight: true
            Layout.maximumWidth: 250

            Button {
                id: first_btn
                Layout.fillWidth: true
    
                text: qsTr("Start via thread object")
                onClicked: controller.startViaThreadObject()
            }

            Button {
                id: second_btn
                Layout.fillWidth: true

                text: qsTr("Start via signals")
                onClicked: controller.startViaSignals()
            }

            Item {
                Layout.fillHeight: true
            }
        }
    }

    MessageDialog 
    {
        id: messageDialog
        title: ""
        text: ""
        onAccepted: 
        {
            messageDialog.close()  
        }
        
        function showMessageBox(title: string, message: string)
        {
            messageDialog.text = message
            messageDialog.title = title
            messageDialog.open()  
        }
    }

    Connections {
        target: controller

        function onNewLog(msg) {
            console.log(`new message: ${msg}`)
            logModel.append({'msg': msg})
        }
    }

    Component.onCompleted: 
    {
    }
}
