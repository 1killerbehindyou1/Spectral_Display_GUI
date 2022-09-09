import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Window 
{
    id: root
    width: 900
    height: 600
    visible: true
    title: qsTr("Basic Gui")
    color: "lightgrey"
    
    SplitView 
    { 
        anchors.fill: parent
        
        ColumnLayout
        {
            MenuBar 
            {       
                contentWidth: parent.width
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
            
            DrawPanel
            {
                implicitWidth: 720
                implicitHeight: root.height 
            }
        }

        ScrollView
        {
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            
             ControlPanel
            {
                implicitHeight: 600
                implicitWidth: 180
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
     

