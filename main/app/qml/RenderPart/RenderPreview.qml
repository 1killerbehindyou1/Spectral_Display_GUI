import QtQuick.Window 2.15
import QtQuick.Dialogs 1.3
import Main 1.0
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.15

// Preview panel presenting a rotating row of LEDs with speed-dependent blur.
Control
{
    id: root

    /**
        blurBase: minimum blur applied even at low speed.
        Higher values can be used to exaggerate the effect for demonstration purposes.
     */
    property real blurBase: 16

    /**
        currentSpeedDegPerSecond: smoothed speed used by the animation.
        rotationAngle: current angle of the rotating content. Updated in a timer loop by integrating the current speed.
        Note: this is not intended to be an accurate physics simulation, just a visually plausible effect for demonstration purposes.
        blurBase: minimum blur applied even at low speed.
            Higher values can be used to exaggerate the effect for demonstration purposes.
     */
    property real currentSpeedDegPerSecond: 0

    /**
        rotationAngle: current angle of the rotating content. Updated in a timer loop by integrating the current speed.
        Note: this is not intended to be an accurate physics simulation, just a visually plausible effect for demonstration purposes.
     */
    property real rotationAngle: 0

    /*  targetSpeedDegPerSecond: value requested by the user (slider).*/
    property real targetSpeedDegPerSecond: speedSlider.value
    property int wrapperLedCount: Math.max(1, renderItem.ledCount)
    property int wrapperLedDistance: Math.max(0, renderItem.ledDistance)
    property int wrapperLedSize: Math.max(1, renderItem.ledSize)

    function checkRenderedPreview(state)
    {
        renderItem.startRendering(state);
    }
    function getOutImage()
    {
        return renderItem.image;
    }
    function onAngularResolutionChanged(angRes)
    {
        console.log("onAngularResolutionChanged: " + angRes);
        renderItem.updateAngularResolution(angRes);
        renderItem.requestRepaint();
    }
    function onLedDistanceChanged(distance)
    {
        console.log("onLedDistanceChanged: " + distance);
        renderItem.updateLedDistance(distance);
        renderItem.requestRepaint();
    }
    function onLedNumChanged(no_pixels)
    {
        console.log("onLedNumChanged: " + no_pixels);
        renderItem.updateNoOfPixels(no_pixels);
        renderItem.requestRepaint();
    }
    function onLedSizeChanged(size)
    {
        console.log("onLedSizeChanged: " + size);
        renderItem.updateLedSize(size);
        renderItem.requestRepaint();
    }
    function onRotationSpeedChanged(speed)
    {
        console.log("onRotationSpeedChanged: " + speed);
        renderItem.updateRotationSpeed(speed);
        renderItem.requestRepaint();
    }
    function requestRepaint()
    {
        renderItem.requestRepaint();
    }
    function setPixmap(pixmapPointer)
    {
        renderItem.setPixmap(pixmapPointer);
        renderItem.requestRepaint();
    }
    function syncWrapperFromRender()
    {
        wrapperLedSize = Math.max(1, renderItem.ledSize);
        wrapperLedDistance = Math.max(0, renderItem.ledDistance);
        wrapperLedCount = Math.max(1, renderItem.ledCount);
    }

    implicitHeight: 500
    implicitWidth: 720

    /**
        Behavior on currentSpeedDegPerSecond adds inertia so speed changes are smooth instead of abrupt.
    */
    Behavior on currentSpeedDegPerSecond
    {
        /**
            Adds inertia so speed changes are smooth instead of abrupt.
         */
        SmoothedAnimation
        {
            duration: 260 // Duration is a fallback to prevent very long transitions at low speeds.
            maximumEasingTime: 400 // Maximum time to reach target value, even at very low speeds.
            velocity: 200 // Higher velocity means less inertia and faster response to changes.
        }
    }

    Component.onCompleted:
    {
        root.syncWrapperFromRender();
        renderItem.requestRepaint();
    }

    RenderEngine
    {
        id: renderItem
    }

    // Neutral preview background.
    Rectangle
    {
        anchors.fill: parent
        color: "white"
    }
    Timer
    {
        id: rotationTick
        // ~60 FPS update loop for rotation integration.
        interval: 15
        repeat: true
        running: true

        onTriggered: {
            // Move current speed toward target speed and integrate angle over time.
            root.currentSpeedDegPerSecond = root.targetSpeedDegPerSecond;
            root.rotationAngle = (root.rotationAngle + (root.currentSpeedDegPerSecond * interval / 1000.0)) % 360;
        }
    }
    ColumnLayout {
        anchors.fill: parent
        spacing: 6

        Rectangle {
            Layout.fillHeight: true
            Layout.fillWidth: true
            color: "transparent"

            Item {
                id: previewArea
                anchors.fill: parent

                Item {
                    // Container rotated as a whole around its origin.
                    id: rotatingContent
                    anchors.centerIn: parent
                    height: squaresRow.height
                    rotation: root.rotationAngle
                    transformOrigin: Item.Left
                    width: squaresRow.width

                    Row {
                        // Source geometry: 10 red rectangles in one line.
                        id: squaresRow
                        spacing: wrapperLedDistance

                        Repeater {
                            id: squaresRepeater
                            model: wrapperLedCount

                            Rectangle {
                                id: qml_wrapper
                                color: "red"
                                height: wrapperLedSize
                                width: wrapperLedSize
                            }
                        }
                    }
                    ShaderEffectSource {
                        // Offscreen capture of the source row for post-processing.
                        id: renderedSource
                        height: rotatingContent.height
                        hideSource: true
                        live: true
                        smooth: true
                        sourceItem: squaresRow
                        width: rotatingContent.width
                    }
                    FastBlur {
                        // Motion-like blur intensity increases with speed.
                        anchors.fill: parent
                        radius: Math.min(64, root.blurBase + Math.abs(root.currentSpeedDegPerSecond) / 4)
                        source: renderedSource
                        transparentBorder: true
                    }
                    ShaderEffectSource {
                        // Sharp overlay to keep the row readable while blurred.
                        anchors.fill: parent
                        hideSource: true
                        live: true
                        opacity: 0.62
                        smooth: true
                        sourceItem: squaresRow
                    }
                }
            }
            Row {
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 30

                Label {
                    text: "Speed: " + Math.round(root.currentSpeedDegPerSecond) + "°/s"
                }
                Label {
                    text: "Blur: " + Math.round(Math.min(64, root.blurBase + Math.abs(root.currentSpeedDegPerSecond) / 4))
                }
                Slider {
                    id: speedSlider
                    // User control for target rotation speed.
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
            console.log("RenderPreview image size:", transform_engine.transformedWidth, "x", transform_engine.transformedHeight);
            renderItem.requestRepaint();
        }

        target: transform_engine
    }
}
