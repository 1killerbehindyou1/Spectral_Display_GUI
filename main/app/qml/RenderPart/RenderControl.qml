import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0
import "../Controls"
import "../Utils"

Control
{
    id: root
    signal ledNumChanged(int num)
    signal ledRotationChanged(int rotation)
    signal ledSizeChanged(int size)
    signal ledDistanceChanged(int distance)

    function clampInt(value, minValue, maxValue)
    {
        return Math.max(minValue, Math.min(maxValue, parseInt(value)));
    }

    function exportSettings()
    {
        return {
            ledCount: led_num.value,
            ledAngle: led_rotation.value,
            ledSize: led_size.value,
            ledDistance: led_distance.value
        };
    }

    function applySettings(settings)
    {
        if (!settings)
        {
            return;
        }

        led_num.setCurrentValue(
            clampInt(settings.ledCount !== undefined ? settings.ledCount : led_num.init_value,
                     led_num.min, led_num.max));
        led_rotation.setCurrentValue(
            clampInt(settings.ledAngle !== undefined ? settings.ledAngle : led_rotation.init_value,
                     led_rotation.min, led_rotation.max));
        led_size.setCurrentValue(
            clampInt(settings.ledSize !== undefined ? settings.ledSize : led_size.init_value,
                     led_size.min, led_size.max));
        led_distance.setCurrentValue(
            clampInt(settings.ledDistance !== undefined ? settings.ledDistance : led_distance.init_value,
                     led_distance.min, led_distance.max));

        root.ledNumChanged(led_num.value);
        root.ledRotationChanged(led_rotation.value);
        root.ledSizeChanged(led_size.value);
        root.ledDistanceChanged(led_distance.value);
    }

    implicitWidth: 500
    implicitHeight: 500
    padding: 10
    background: Rectangle{color: "#c8d6e8"}

    contentItem: ColumnLayout
    {
        anchors.fill: parent
        spacing: 10
        FillingRect{Layout.fillWidth: true; fillerHeight: 10}

        GroupBox
        {
            title: "Spectral display parameters"
             font.pixelSize: 18
             font.bold: true
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop

            contentItem: ColumnLayout
            {
                spacing: 20
                Layout.alignment: Qt.AlignTop

                DataInput{ id: led_num; label: "number of LEDs"; init_value: 25;  max: 200; min: 1}
                DataInput{ id: led_rotation; label:"LED angle"; init_value: 5;  max: 360; min: 1}
                DataInput{ id: led_size; label:"LED size"; init_value: 5;  max: 360; min: 1}
                DataInput{ id: led_distance; label:"LED distance"; init_value: 2;  max: 10; min: 0}

                Text{text: "Spectral display resolution: "; font.bold: true; font.pixelSize: 18 }
                TextField
                {
                    readOnly: true
                    text: parseInt(360/led_rotation.value) + " x " + led_num.value + " pixels";
                    color: "black"
                    font.pixelSize: 20
                    activeFocusOnTab: false
                    background: Rectangle {color: "transparent"}
                }
            }
            FillingRect{Layout.fillHeight: true}
            FillingRect{fillerHeight: 30}
        }
    }

    Component.onCompleted:
    {
        led_num.update.connect(function() { root.ledNumChanged(led_num.value); });
        led_rotation.update.connect(function() { root.ledRotationChanged(led_rotation.value); });
        led_size.update.connect(function() { root.ledSizeChanged(led_size.value); });
        led_distance.update.connect(function() { root.ledDistanceChanged(led_distance.value); });

        root.ledNumChanged(led_num.init_value);
        root.ledRotationChanged(led_rotation.init_value);
        root.ledSizeChanged(led_size.init_value);
        root.ledDistanceChanged(led_distance.init_value);
    }
}




