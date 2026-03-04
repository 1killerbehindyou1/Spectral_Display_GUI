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
        return;
    }

    function getOutImage()
    {
        return transform_engine ? transform_engine.transformedImage : null;
    }

    // function setPixmap()
    // {
    //     return;
    // }

    // function updateLedParameters(size: int, angle: int, num: int)
    // {
    //     return transform_engine.updateTransformParameters(num, angle, size);
    // }



    // function checkRenderedPreview(state: bool)
    // {
    //     return render.startRendering(state);
    // }

    // function updatePoint(mouseX: real, mouseY: real)
    // {
    //     return transform_engine.updatePoint(Qt.point(mouseX, mouseY));
    // }

    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }

    // contentItem: LedRuler
    // {
    //     id: render
    //     anchors.fill: parent
    // }

    // Connections
    // {
    //     target: transform_engine
    //     function onTransformReadyForQml()
    //     {
    //         render.image = transform_engine.transformedImage
    //         render.requestRepaint()
    //     }
    // }
}