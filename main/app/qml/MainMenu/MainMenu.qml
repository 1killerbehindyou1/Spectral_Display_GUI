import QtQuick 2.15
import QtQuick.Controls 2.15

MenuBar
{
    id: root
    property alias showSelectedImage: showSelectedImage
    property alias showRenderedPreview: showRenderedPreview

    contentWidth: parent ? parent.width : implicitWidth

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