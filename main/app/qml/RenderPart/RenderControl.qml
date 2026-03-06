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

    property bool renderingActive: false
    signal startRenderingRequested
    signal stopRenderingRequested

    signal ledDistanceChanged(int distance)
    signal ledNumChanged(int num)
    signal ledRotationChanged(int rotation)
    signal ledRotationSpeedChanged(int speed)
    signal ledSizeChanged(int size)

    function applySettings(settings)
    {
        if (!settings)
        {
            return;
        }

        led_num.setCurrentValue(clampInt(settings.ledCount !== undefined ? settings.ledCount : led_num.init_value, led_num.min, led_num.max));
        led_rotation.setCurrentValue(clampInt(settings.ledAngle !== undefined ? settings.ledAngle : led_rotation.init_value, led_rotation.min, led_rotation.max));
        led_size.setCurrentValue(clampInt(settings.ledSize !== undefined ? settings.ledSize : led_size.init_value, led_size.min, led_size.max));
        led_distance.setCurrentValue(clampInt(settings.ledDistance !== undefined ? settings.ledDistance : led_distance.init_value, led_distance.min, led_distance.max));
        led_rotation_speed.setCurrentValue(clampInt(settings.ledRotationSpeed !== undefined ? settings.ledRotationSpeed : led_rotation_speed.init_value, led_rotation_speed.min, led_rotation_speed.max));
        root.ledNumChanged(led_num.value);
        root.ledRotationChanged(led_rotation.value);
        root.ledSizeChanged(led_size.value);
        root.ledDistanceChanged(led_distance.value);
        root.ledRotationSpeedChanged(led_rotation_speed.value);
    }

    function clampInt(value, minValue, maxValue) {
        return Math.max(minValue, Math.min(maxValue, parseInt(value)));
    }
    function cpuUsageColor(cpuPercent) {
        if (cpuPercent >= 80) {
            return "#c0392b";
        }
        if (cpuPercent >= 50) {
            return "#d4ac0d";
        }
        return "#1e8449";
    }
    function exportSettings() {
        return {
            "ledCount": led_num.value,
            "ledAngle": led_rotation.value,
            "ledSize": led_size.value,
            "ledDistance": led_distance.value,
            "ledRotationSpeed": led_rotation_speed.value
        };
    }
    function ramUsageColor(ramMb) {
        if (ramMb >= 800) {
            return "#c0392b";
        }
        if (ramMb >= 400) {
            return "#d4ac0d";
        }
        return "#1e8449";
    }

    implicitHeight: 500
    implicitWidth: 500
    padding: 10

    background: Rectangle
    {
        color: "#c8d6e8"
    }

    contentItem: ColumnLayout
    {
        anchors.fill: parent
        spacing: 10

        FillingRect { Layout.fillWidth: true; fillerHeight: 10}

        GroupBox
        {
            title: "Spectral display parameters"
            font.bold: true
            font.pixelSize: 18

            Layout.alignment: Qt.AlignTop
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height
            Layout.preferredWidth: parent.width


            contentItem: ColumnLayout
            {
                Layout.alignment: Qt.AlignTop
                spacing: 20

                DataInput {
                    id: led_num
                    init_value: 25
                    label: "number of LEDs"
                    max: 200
                    min: 1
                }
                DataInput {
                    id: led_rotation
                    init_value: 5
                    label: "LED angle"
                    max: 360
                    min: 1
                }
                DataInput {
                    id: led_size
                    init_value: 5
                    label: "LED size"
                    max: 360
                    min: 1
                }
                DataInput {
                    id: led_distance
                    init_value: 2
                    label: "LED distance"
                    max: 10
                    min: 0
                }
                DataInput {
                    id: led_rotation_speed
                    init_value: 600
                    label: "rotation speed [RPM]"
                    max: 6000
                    min: 1
                }
                Text {
                    font.bold: true
                    font.pixelSize: 18
                    text: "Spectral display resolution: "
                }
                TextField {
                    activeFocusOnTab: false
                    color: "black"
                    font.pixelSize: 20
                    readOnly: true
                    text: parseInt(360 / led_rotation.value) + " x " + led_num.value + " pixels"

                    background: Rectangle
                    {
                        color: "transparent"
                    }
                }
                Text
                {
                    font.bold: true
                    font.pixelSize: 16
                    text: "Resource usage (during rendering):"
                }
                Text {
                    color: root.cpuUsageColor(process_monitor ? process_monitor.cpuPercent : 0)
                    font.pixelSize: 14
                    text: "CPU: " + (process_monitor ? process_monitor.cpuPercent.toFixed(1) : "0.0") + "%"
                }
                Text {
                    color: root.ramUsageColor(process_monitor ? process_monitor.ramMb : 0)
                    font.pixelSize: 14
                    text: "RAM: " + (process_monitor ? process_monitor.ramMb.toFixed(1) : "0.0") + " MB"
                }
                RowLayout
                {
                    Layout.fillWidth: true
                    spacing: 8

                    Button
                    {
                        id: but_start
                        Layout.fillWidth: true
                        enabled: true
                        text: "Start rendering"
                        onClicked:
                        {
                            but_stop.enabled = true;
                            but_start.enabled = false;
                            root.renderingActive = true;
                        }
                    }

                    Button
                    {
                        id: but_stop
                        Layout.fillWidth: true
                        enabled: false
                        text: "Stop rendering"
                        onClicked:
                        {
                            but_start.enabled = true;
                            but_stop.enabled = false;
                            root.renderingActive = false;
                        }
                    }
                }
            }

            FillingRect {
                Layout.fillHeight: true
            }
            FillingRect {
                fillerHeight: 30
            }
        }
    }

    Timer
    {
        interval: 1000
        repeat: true
        running: true

        onTriggered:
        {
            if (process_monitor) {
                process_monitor.refresh();
            }
        }
    }

    Component.onCompleted:
    {
        led_num.update.connect(function () {
                root.ledNumChanged(led_num.value);
            });
        led_rotation.update.connect(function () {
                root.ledRotationChanged(led_rotation.value);
            });
        led_size.update.connect(function () {
                root.ledSizeChanged(led_size.value);
            });
        led_distance.update.connect(function () {
                root.ledDistanceChanged(led_distance.value);
            });
        led_rotation_speed.update.connect(function () {
                root.ledRotationSpeedChanged(led_rotation_speed.value);
            });

        root.ledNumChanged(led_num.init_value);
        root.ledRotationChanged(led_rotation.init_value);
        root.ledSizeChanged(led_size.init_value);
        root.ledDistanceChanged(led_distance.init_value);
        root.ledRotationSpeedChanged(led_rotation_speed.init_value);

        if(process_monitor)
        {
            process_monitor.refresh();
        }
    }
}
