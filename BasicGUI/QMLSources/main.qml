import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Window 
{
    width: 900
    height: 600
    visible: true
    title: qsTr("Basic Gui")
    color: "lightgrey"
    maximumHeight: 600 
    minimumHeight: 600
    maximumWidth: 900
    minimumWidth: 900


    SplitView 
    { 
        anchors.fill: parent
        ColumnLayout
        {
            MenuBar 
            {       
                Menu 
                {
                    title: qsTr("&File")
                    Action 
                    {
                        text: qsTr("&Open...")
                        onTriggered:
                        {
                            fileDialog.open()
                        }
                    }
                    MenuSeparator { }
                    Action { text: qsTr("&Close") }
                }
                Menu 
                {
                    title: qsTr("&Help")
                    Action { text: qsTr("&About") }
                }
            }
          
            Control
            { 
                implicitWidth: 720
                height: 520 
                
            
            contentItem: MouseArea
                {
                    anchors.fill: parent
                    LedRuler
                    {
                        id: led          
                        anchors.fill: parent
                        color: "blue"
                        size: 100
                        lx: 50
                        ly: 50               
                    }
                    onPressed:{led.rulerUpdate(mouseX, mouseY, l_rot.value)}
                }                                  
            }
        }
        Control
        {
            background: Rectangle
            {
                color: "#AAA"
            }
            
            implicitWidth: 180
            
            ColumnLayout
            { 
                spacing: 10; 
                anchors.bottom: parent.bottom
                anchors.margins: 30

                Text{text: "Led ruler parameters" }         
                DataInput{ id: l_x; value: "50"; label:"x position  "}
                DataInput{ id: l_y; value: "50"; label:"y position  "}
                DataInput{ id: l_size; value: "100"; label: "led size     "}
                DataInput{ id: l_rot; value: "0"; label:"led rotation"}      
                
                Button
                {
                    text: "SET"
                    onClicked: 
                    {
                        led.size = l_size.value
                        led.rulerUpdate(l_x.value, l_y.value, l_rot.value)
                    }          
                }
                                    
            }
        }
    }
    
    FileDialog 
    {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        onAccepted:
        {
            led.setPixMap(fileDialog.fileUrls)
        }
        onRejected: 
        {
           fileDialog.close()
        }
        Component.onCompleted: visible = false
    }
}
     

