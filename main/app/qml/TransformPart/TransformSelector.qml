import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    signal pointUpdate(real xPosition, real yPosition)
    property int defaultSelectorRadius: 100

    function mapToSourcePoint(mouseX: real, mouseY: real)
    {
        const srcW = loaded_image.sourceSize.width > 0 ? loaded_image.sourceSize.width : loaded_image.width;
        const srcH = loaded_image.sourceSize.height > 0 ? loaded_image.sourceSize.height : loaded_image.height;

        if (srcW <= 0 || srcH <= 0 || root.width <= 0 || root.height <= 0)
        {
            return Qt.point(mouseX, mouseY);
        }

        const scale = Math.max(root.width / srcW, root.height / srcH);
        const paintedW = srcW * scale;
        const paintedH = srcH * scale;
        const offsetX = (root.width - paintedW) / 2.0;
        const offsetY = (root.height - paintedH) / 2.0;

        let mappedX = (mouseX - offsetX) / scale;
        let mappedY = (mouseY - offsetY) / scale;

        mappedX = Math.max(0, Math.min(srcW - 1, mappedX));
        mappedY = Math.max(0, Math.min(srcH - 1, mappedY));

        console.log("mapToSourcePoint: mouseX: " + mouseX + ", mouseY: " + mouseY + ", mappedX: " + mappedX + ", mappedY: " + mappedY);
        return Qt.point(Math.round(mappedX), Math.round(mappedY));
    }

    function onRadiusChanged(radius: int)
    {
        return selector_local.selectorResize(radius);
    }

    property alias img_visible: loaded_image.visible
    property alias img_source:  loaded_image.source

    id: root
    implicitWidth: 500
    implicitHeight: 500

    background: Rectangle
    {
        color: "white"
    }

    contentItem: Image
    {
        id: loaded_image
        visible: true
        fillMode: Image.PreserveAspectCrop
    }

    Selector
    {
        id: selector_local
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                const mappedPoint = root.mapToSourcePoint(mouseX, mouseY);
                console.log("line: 73 , file: RenderSelector.qml " + "mappedX: " + mappedPoint.x + ", mappedY: " + mappedPoint.y);
                selector_local.setPoint(Qt.point(mouseX, mouseY));
                root.pointUpdate(mappedPoint.x, mappedPoint.y);
            }
        }
    }

    Component.onCompleted:
    {
        console.log("Component completed, setting default selector radius: " + defaultSelectorRadius);
        selector_local.selectorResize(defaultSelectorRadius);
    }

}

