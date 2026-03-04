import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root

    function checkRenderedPreview(state)
    {
        render.startRendering(state);
    }

    function getOutImage()
    {
        return render.image;
    }

    function setPixmap(pixmapPointer)
    {
        render.setPixmap(pixmapPointer);
        render.requestRepaint();
    }

    function repaintOnClick()
    {
        render.requestRepaint();
    }

    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }

    contentItem: Item
    {
        anchors.fill: parent

        LedRuler
        {
            id: render
            anchors.fill: parent
        }

        MouseArea
        {
            anchors.fill: parent
            onClicked: root.repaintOnClick()
        }
    }

    Connections
    {
        target: transform_engine
        function onTransformReadyForQml()
        {
            render.image = transform_engine.transformedImage;
            render.requestRepaint();
        }
    }
}