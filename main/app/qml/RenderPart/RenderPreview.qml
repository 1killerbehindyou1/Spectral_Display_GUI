import QtQuick.Window 2.15
import Main 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

Control
{
    id: root

    property real blurBase: 16
    property real currentSpeedDegPerSecond: 0
    property real rotationAngle: 0
    property real targetSpeedDegPerSecond: speedSlider.value
    property bool renderingActive: false
    property int wrapperLedCount: Math.max(1, renderItem.ledCount)
    property int wrapperLedDistance: Math.max(0, renderItem.ledDistance)
    property int wrapperLedSize: Math.max(1, renderItem.ledSize)

    function checkRenderedPreview(state)
    {
        root.renderingActive = !!state;
        renderItem.startRendering(state);
    }

    function getOutImage()
    {
        return renderItem.image;
    }
    function onAngularResolutionChanged(angRes) {
        renderItem.updateAngularResolution(angRes);
        renderItem.requestRepaint();
    }
    function onLedDistanceChanged(distance) {
        renderItem.updateLedDistance(distance);
        renderItem.requestRepaint();
    }
    function onLedNumChanged(no_pixels) {
        renderItem.updateNoOfPixels(no_pixels);
        renderItem.requestRepaint();
    }
    function onLedSizeChanged(size) {
        renderItem.updateLedSize(size);
        renderItem.requestRepaint();
    }
    function onRotationSpeedChanged(speed) {
        renderItem.updateRotationSpeed(speed);
        renderItem.requestRepaint();
    }
    function requestRepaint() {
        renderItem.requestRepaint();
    }
    function setPixmap(pixmapPointer) {
        renderItem.setPixmap(pixmapPointer);
        renderItem.requestRepaint();
    }
    function syncWrapperFromRender() {
        wrapperLedSize = Math.max(1, renderItem.ledSize);
        wrapperLedDistance = Math.max(0, renderItem.ledDistance);
        wrapperLedCount = Math.max(1, renderItem.ledCount);
    }

    implicitHeight: 500
    implicitWidth: 720

    Behavior on currentSpeedDegPerSecond {
        SmoothedAnimation {
            duration: 260
            maximumEasingTime: 400
            velocity: 200
        }
    }

    Component.onCompleted: {
        root.syncWrapperFromRender();
        renderItem.requestRepaint();
    }

    RenderEngine
    {
        id: renderItem
    }

    Rectangle
    {
        anchors.fill: parent
        color: "white"
    }

    Timer
    {
        id: rotationTick
        interval: 15
        repeat: true
        running: root.renderingActive

        onTriggered: {
            root.currentSpeedDegPerSecond = root.targetSpeedDegPerSecond;
            root.rotationAngle = (root.rotationAngle + (root.currentSpeedDegPerSecond * interval / 1000.0)) % 360;
        }
    }

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 6

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            Item
            {
                anchors.fill: parent

                Item
                {
                    id: rotatingContent
                    anchors.centerIn: parent
                    height: squaresRow.height
                    rotation: root.rotationAngle
                    transformOrigin: Item.Center
                    width: squaresRow.width

                    Row
                    {
                        id: squaresRow
                        spacing: wrapperLedDistance

                        Repeater
                        {
                            model: wrapperLedCount

                            Rectangle
                            {
                                height: wrapperLedSize
                                width: wrapperLedSize
                                color: "red"
                            }
                        }
                    }

                    ShaderEffectSource
                    {
                        id: renderedSource
                        height: rotatingContent.height
                        hideSource: true
                        live: true
                        smooth: true
                        sourceItem: squaresRow
                        width: rotatingContent.width
                    }

                    FastBlur
                    {
                        anchors.fill: parent
                        radius: Math.min(64, root.blurBase + Math.abs(root.currentSpeedDegPerSecond) / 4)
                        source: renderedSource
                        transparentBorder: true
                    }

                    ShaderEffectSource
                    {
                        anchors.fill: parent
                        hideSource: true
                        live: true
                        opacity: 0.62
                        smooth: true
                        sourceItem: squaresRow
                    }
                }
            }
            Row
            {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30

                Label {
                    text: "Speed: " + Math.round(root.currentSpeedDegPerSecond) + "°/s"
                }
                Label {
                    text: "Blur: " + Math.round(Math.min(64, root.blurBase + Math.abs(root.currentSpeedDegPerSecond) / 4))
                }

                Slider
                {
                    id: speedSlider
                    Layout.fillWidth: true
                    from: 0
                    stepSize: 1
                    to: 2000
                    value: 40
                }
            }
        }
    }

    Connections {
        function onLedCountChanged() {
            root.wrapperLedCount = Math.max(1, renderItem.ledCount);
        }
        function onLedDistanceChanged() {
            root.wrapperLedDistance = Math.max(0, renderItem.ledDistance);
        }
        function onLedSizeChanged() {
            root.wrapperLedSize = Math.max(1, renderItem.ledSize);
        }

        target: renderItem
    }

    Connections {
        function onTransformReadyForQml() {
            renderItem.image = transform_engine.transformedImage;
            renderItem.requestRepaint();
        }

        target: transform_engine
    }
}
