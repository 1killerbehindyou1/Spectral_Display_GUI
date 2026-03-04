import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    property real zoomFactor: 3.0
    property int previewRotation: 180

    function onSelectorClicked(xPosition, yPosition)
    {
        transform_engine.updatePoint(Qt.point(xPosition, yPosition));
    }

    function updatePreview()
    {
        preview_image.source = "image://live/frame?t=" + Date.now();
    }

    background: Rectangle
    {
        color: "white"
    }

    contentItem: Item
    {
        anchors.fill: parent

        Image
        {
            id: preview_image
            anchors.fill: parent
            scale: root.zoomFactor
            transformOrigin: Item.Center
            fillMode: Image.PreserveAspectFit
            rotation: root.previewRotation
            cache: false
        }

        Button
        {
            anchors.top: parent.top
            anchors.right: parent.right
            anchors.margins: 8
            text: "Obróć 90°"
            onClicked: root.previewRotation = (root.previewRotation + 90) % 360
        }
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