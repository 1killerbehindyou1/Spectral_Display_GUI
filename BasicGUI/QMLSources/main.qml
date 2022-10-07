import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

ApplicationWindow 
{
    id: root
    width: 900
    height: 600
    visible: true
    title: qsTr("Basic Gui")
    color: "lightgrey"
    menuBar: MenuBar 
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

    SplitView 
    { 
        anchors.fill: parent
        
        RenderPanel
        { 
            id: drawing
        }

        ImagePanel
        {
            id: id_picture
        }

        ControlPanel
        {
            id: parameters
            SplitView.minimumWidth: parameters.implicitWidth
        }
    }
    
    FileDialog 
    {
        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectMultiple: false
        onAccepted:
        {
           id_picture.loadImageFromFile(fileDialog.fileUrl)
        }
        onRejected: 
        {
           fileDialog.close()
        }
        Component.onCompleted: visible = false
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
    Component.onCompleted: 
    {
        parameters.newParameters.connect(drawing.updateLedParameters) //connection slot and signals
        id_picture.fileLoadErrorInfo.connect(messageDialog.showMessageBox) //printing connection errors
    }
}
     

