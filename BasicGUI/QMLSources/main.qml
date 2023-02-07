import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

ApplicationWindow
{
    id: root
    width: 1300
    height: 600
    visible: true
    title: qsTr("Basic Gui")
    color: "lightgrey"

    property bool imageSelected: false
    property bool previewIsActive: showSelectedImage.checked
    property bool renderedPreviewIsActive: showRenderedPreview.checked
    property string file_operation: ""

    onPreviewIsActiveChanged: selector.img_visible = imageSelected && previewIsActive;
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
        id: split_View

        Image
        {
            id: selector
            width: (parent.width - parameters.width)/2
        }


        handle: Rectangle
        {
            implicitWidth: 4
            implicitHeight: 4
            color: SplitHandle.pressed ? "#243956"
                : (SplitHandle.hovered ? Qt.lighter("#243956", 1.5) : Qt.lighter("#243956", 2))
        }

        RenderPanel
        {
            id: drawing
            width: (parent.width - parameters.width)/2
        }
            ControlPanel
        {
            id: parameters
            //implicitWidth: 300
            //SplitView.minimumWidth: 250
            //SplitView.preferredWidth: 300
        }

        Component.onCompleted: parameters.width = 250

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
                selector.img_source = fileDialog.fileUrl;
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
        parameters.parameterChanged.connect(selector.selectorParameterChanged);
        parameters.parameterChanged.connect(drawing.updateLedParameters);
        fileDialog.pixmapLoaded.connect(drawing.setPixmap);
        selector.pointUpdate.connect(drawing.updatePoint);
    }
}


