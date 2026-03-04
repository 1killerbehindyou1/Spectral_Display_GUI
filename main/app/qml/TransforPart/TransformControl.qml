import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0
import "../Controls"

Control
{
    id: root
    signal parameterChanged(int size, int rotation , int number_of_leds)
    signal zoomChanged(real zoomFactor)
    signal radiusChanged(int radius)

    function onUpdate()
    {
        if (transform_engine)
        {
            transform_engine.updateTransformParameters(l_num.value, l_rotation.value, l_size.value);
        }
        return root.parameterChanged(l_size.value, l_rotation.value, l_num.value )
    }

    function onRadiusUpdate()
    {
        console.log("radius changed: " + l_radius.value);
        return root.radiusChanged(l_radius.value);
    }
    function onZoomUpdate()
    {
        console.log("zoom changed: " + l_zoom.value);
        return root.zoomChanged(l_zoom.value)
    }

    implicitWidth: 500
    implicitHeight: 500
    padding: 10
    background: Rectangle
    {
        color: "#c8d6e8"
    }

    contentItem: ColumnLayout
    {
        anchors.fill: parent
        spacing: 10

        GroupBox
        {
             title: "Parameters"
             font.pixelSize: 15
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop

             contentItem: ColumnLayout
             {
                spacing: 20
                Text{text: "Spectral display hardware"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_num; label: "led number"; init_value: 25;  max: 200; min: 1}
                DataInput{ id: l_rotation; label:"led angle"; init_value: 5;  max: 360; min: 1}
                DataInput{ id: l_size; label:"led size"; init_value: 5;  max: 360; min: 1}
                ColumnLayout
                {
                    Text{text: "Spectral display resolution: "; font.pixelSize: 18 }
                    TextField
                    {
                        readOnly: true
                        text: parseInt(360/l_rotation.value) + " x " + l_num.value + " pixels";
                        color: "black"
                        font.pixelSize: 20
                        activeFocusOnTab: false
                        background: Rectangle {color: "transparent"}
                    }
                }

                Rectangle
                {
                    height: 1
                    border.width: 2
                    color: "#b1b9c5"
                    Layout.fillWidth: true
                }

                Text{text: "Selector radius [pixels]"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_radius; label: "Radius: "; init_value: 100;  max: 240; min: 1}

                Text{text: "Output preview zoom"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_zoom; label: "Zoom [x]: "; init_value: 3; max: 10; min: 1 }
                ColumnLayout
                {
                    Text{text: "Transformed image size: "; font.pixelSize: 18 }
                    TextField
                    {
                        readOnly: true
                        text: transform_engine && transform_engine.transformedWidth > 0 && transform_engine.transformedHeight > 0
                              ? transform_engine.transformedWidth + " x " + transform_engine.transformedHeight + " pixels"
                              : "-"
                        color: "black"
                        font.pixelSize: 20
                        activeFocusOnTab: false
                        background: Rectangle {color: "transparent"}
                    }
                }
                Rectangle
                {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    color: "transparent"
                    border.width: 0
                    border.color: "transparent"
                }
            }
        }
    }

    Component.onCompleted:
    {
        l_num.update.connect(onUpdate);
        l_rotation.update.connect(onUpdate);
        l_zoom.update.connect(onZoomUpdate);
        l_radius.update.connect(onRadiusUpdate);

        root.zoomChanged(l_zoom.init_value);
        root.radiusChanged(l_radius.init_value);
        root.parameterChanged(l_radius.init_value, l_rotation.init_value, l_num.init_value);

        if (transform_engine)
        {
            transform_engine.updateTransformParameters(l_num.init_value, l_rotation.init_value, l_radius.init_value);
        }
    }
}




