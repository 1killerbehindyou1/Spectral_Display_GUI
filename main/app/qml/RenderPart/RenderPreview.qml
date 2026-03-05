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

    function requestRepaint()
    {
        render.requestRepaint();
    }

    function onLedNumChanged(no_pixels)
    {
        console.log("onLedNumChanged: " + no_pixels);
        render.updateNoOfPixels(no_pixels);
        render.requestRepaint();
    }

    function onLedSizeChanged(size)
    {
        console.log("onLedSizeChanged: " + size);
        render.updateLedSize(size);
        render.requestRepaint();
    }

    function onLedDistanceChanged(distance)
    {
        console.log("onLedDistanceChanged: " + distance);
        render.updateLedDistance(distance);
        render.requestRepaint();
    }

     function onAngularResolutionChanged(angRes)
     {
        console.log("onAngularResolutionChanged: " + angRes);
        render.updateAngularResolution(angRes);
        render.requestRepaint();
     }

     implicitWidth: 720
     implicitHeight: 500

     background: Rectangle{ color: "white" }

     contentItem: Item
     {
         anchors.fill: parent

         RenderEngine
         {
             id: render
             anchors.fill: parent
         }

     }

     Connections
     {
         target: transform_engine
         function onTransformReadyForQml()
         {
             render.image = transform_engine.transformedImage;
             console.log(render.image.size());
             render.requestRepaint();
         }
     }

     Component.onCompleted:
     {
         render.requestRepaint();
     }
}