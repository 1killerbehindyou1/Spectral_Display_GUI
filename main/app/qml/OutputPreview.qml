import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root

    function onSelectorClicked(xPosition, yPosition)
    {
        transform_engine.updatePoint(Qt.point(xPosition, yPosition));
        console.log("line: 15 , file: OutputPreview.qml " + "x: " + xPosition + ", y: " + yPosition);
    }

    function updatePreview()
    {
        console.log("line: 20 , file: OutputPreview.qml " + "updating preview");
        preview_image.source = "image://live/frame?t=" + Date.now();
    }

    background: Image
    {
        id: preview_image
        visible: true
        fillMode: Image.PreserveAspectFit
        cache: false
    }

    Connections
    {
        target: transform_engine
        function onTransformReadyForQml()
        {
            root.updatePreview()
        }
    }
}