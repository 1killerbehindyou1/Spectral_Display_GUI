import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    signal pointUpdate(real xPosition, real yPosition)
    property int defaultSelectorRadius: 100
    property real zoomFactor: 3.0

    function mapToSourcePoint(mouseX: real, mouseY: real) {
        const srcW = loaded_image.sourceSize.width > 0 ? loaded_image.sourceSize.width : loaded_image.width;
        const srcH = loaded_image.sourceSize.height > 0 ? loaded_image.sourceSize.height : loaded_image.height;
        const viewW = loaded_image.width;
        const viewH = loaded_image.height;
        if (srcW <= 0 || srcH <= 0 || viewW <= 0 || viewH <= 0) {
            return Qt.point(mouseX, mouseY);
        }
        const baseScale = Math.max(viewW / srcW, viewH / srcH);
        const effectiveScale = baseScale * root.zoomFactor;
        const paintedW = srcW * effectiveScale;
        const paintedH = srcH * effectiveScale;
        const offsetX = (viewW - paintedW) / 2.0;
        const offsetY = (viewH - paintedH) / 2.0;
        let mappedX = (mouseX - offsetX) / effectiveScale;
        let mappedY = (mouseY - offsetY) / effectiveScale;
        mappedX = Math.max(0, Math.min(srcW - 1, mappedX));
        mappedY = Math.max(0, Math.min(srcH - 1, mappedY));
        return Qt.point(Math.round(mappedX), Math.round(mappedY));
    }

    function onRadiusChanged(no_pixels) {
        return selector_local.selectorResize(no_pixels);
    }

    property alias img_visible: loaded_image.visible
    property alias img_source: loaded_image.source
    implicitWidth: 500
    implicitHeight: 500

    background: Rectangle {
        color: "white"
    }

    contentItem: Image {
        id: loaded_image
        scale: root.zoomFactor
        visible: true
        fillMode: Image.PreserveAspectCrop
    }

    Selector {
        id: selector_local
        anchors.fill: parent
        MouseArea {
            anchors.fill: parent
            onClicked: {
                const mappedPoint = root.mapToSourcePoint(mouseX, mouseY);
                selector_local.setPoint(Qt.point(mouseX, mouseY));
                root.pointUpdate(mappedPoint.x, mappedPoint.y);
            }
        }
    }

    Component.onCompleted: {
        selector_local.selectorResize(defaultSelectorRadius);
    }
}
