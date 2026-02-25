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

    function onSelectorClicked(xPosition, yPosition)
    {
        transform_engine.updatePoint(Qt.point(xPosition, yPosition));
    }

    function updatePreview()
    {
        preview_image.source = "image://live/frame?t=" + Date.now();
    }

    background: Image
    {
        id: preview_image
        anchors.fill: parent
        visible: true
        scale: root.zoomFactor
        transformOrigin: Item.Center
        fillMode: Image.PreserveAspectFit
        rotation: 90
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