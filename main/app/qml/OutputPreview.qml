import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root

    function updatePreview()
    {
        preview_image.source = "image://live/frame?t=" + Date.now();
    }

    background: Image
    {
        id: preview_image
        visible: true
        fillMode: Image.PreserveAspectCrop
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