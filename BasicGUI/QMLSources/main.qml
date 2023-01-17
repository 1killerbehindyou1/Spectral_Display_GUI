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

    property bool image_selected: false
    property bool previev_is_active: false

    menuBar: MenuBar 
    {     
        contentWidth: parent.width
        Menu 
        {
            title: qsTr("&File")
            Action 
            {
                text: qsTr("&Load Image...")
                onTriggered:
                {
                    fileDialog.open()            
                }
            }
            MenuSeparator { }
            Action 
            {
                text: qsTr("&Save Transformated Image...")
                onTriggered:
                {
                    fileSaveDialog.open();
                }
            }
        }
        Menu 
        {
            title: qsTr("&View")
            delegate: CheckBox{}

            Action
            {
                checked: previev_is_active
                checkable: true
                text: "Preview selected image..."
                onCheckedChanged: 
                {
                    if(previev_is_active == false)
                    {   
                        previev_is_active = true;
                        if(image_selected)
                        {
                            loaded_image.visible = true;
                        }
                    }
                    else 
                    {
                        previev_is_active = false;
                        if(image_selected)
                        {
                            loaded_image.visible = false;
                        }
                    }
                }
            }

            Action{ text: "Preview rendered image...";}
        }
    }

    SplitView 
    { 
        anchors.fill: parent
        id: splitView
        Image
        {
            anchors.fill: parents
            id: loaded_image
            visible: false
            fillMode: Image.PreserveAspectFit
        }
        
        RenderPanel
        { 
            id: drawing
        }

        ControlPanel
        {
            id: parameters
           
            SplitView.minimumWidth: 400
            SplitView.maximumWidth: 400
        }
    }
    
    FileDialog 
    {
        signal pixmapLoaded()

        id: fileDialog
        title: "Please choose a file"
        nameFilters: [ "Image files (*.jpg *.png)", "All files (*)" ]
        selectMultiple: false
        onAccepted:
        {
           if(file_manager.loadPixMap(fileDialog.fileUrl))
           {
                loaded_image.source = fileDialog.fileUrl;
                image_selected = true;
                fileDialog.pixmapLoaded();
           }
         
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
        parameters.parameterChanged.connect(drawing.updateLedParameters);
        fileDialog.pixmapLoaded.connect(drawing.setPixmap);
    }
}
     

