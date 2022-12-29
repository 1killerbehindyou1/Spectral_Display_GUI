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
                    drawing.saveImage();
                }
            }
        }
        Menu 
        {
            title: qsTr("&View")
            delegate: CheckBox
            {
            }
            Action {
                text: "Preview selected image..."
                checkable: true
                onCheckedChanged: {
                    preview_is_active = value
                    loaded_image.visible = value
                }
                Component.onCompleted: {
                    checked = preview_is_active
                }
            }
            Action {
                text: "Other checkable option"
                checkable: true
            }
            Action {
                text: "Normal option"
            }
        }
    }

    SplitView 
    { 
        anchors.fill: parent
        
        Image
        {
            id: loaded_image
            visible: false

        }
        
        RenderPanel
        { 
            id: drawing
        }
       
        
        ControlPanel
        {
            id: parameters
            
            SplitView.minimumWidth: parameters.implicitWidth
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
     

