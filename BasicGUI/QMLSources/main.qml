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

    property bool imageSelected: false
    property bool previewIsActive: showSelectedImage.checked
    property bool renderedPreviewIsActive: showRenderedPreview.checked
    property string file_operation: ""

    onPreviewIsActiveChanged: loadedImage.visible = imageSelected && previewIsActive;
    onRenderedPreviewIsActiveChanged: drawing.checkRenderedPreview(renderedPreviewIsActive);

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
                    file_operation = "load";
                    fileDialog.title = "Please choose a file";
                    fileDialog.nameFilters = [ "Image files (*.jpg *.png)", "All files (*)" ];
                    fileDialog.selectExisting = true;
                    fileDialog.open();
                }
            }
            MenuSeparator { }
            Action
            {
                text: qsTr("&Save Transformated Image...")
                onTriggered:
                {
                    file_operation = "save";
                    fileDialog.title = "Save to file";
                    fileDialog.nameFilters = [ "Image files (*.jpg *.png)" ];
                    fileDialog.selectExisting = false;
                    fileDialog.open();
                }
            }
        }
        Menu
        {
            title: qsTr("&View")
            delegate: CheckBox{}

            Action
            {
                id: showSelectedImage
                checked: false
                checkable: true
                text: "Preview selected image..."
            }

            Action
            {
                id: showRenderedPreview
                text: "Preview rendered image..."
                checked: false
                checkable: true
            }
        }
    }

    SplitView
    {
        anchors.fill: parent
        id: splitView
        Image
        {
            anchors.fill: parent
            id: loadedImage
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
        selectMultiple: false
        onAccepted:
        {

           if((file_operation == "load")&&(file_manager.loadPixMap(fileDialog.fileUrl)))
           {
                loadedImage.source = fileDialog.fileUrl;
                imageSelected = true;
                fileDialog.pixmapLoaded();
           }
           if(file_operation == "save")
           {
                 file_manager.savePixMap(fileDialog.fileUrl, drawing.getOutImage());
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


