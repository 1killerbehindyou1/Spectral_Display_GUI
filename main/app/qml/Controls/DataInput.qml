import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Control
{
   id: root
    property alias label: label.text
    property alias value: control.value
    property int max
    property int min
    property int init_value

    signal update()

    implicitWidth: 270

    contentItem: ColumnLayout
    {
        RowLayout
        {
            Text
            {
                font.pixelSize: 20
                id: label
            }
            Item{Layout.fillWidth: true}

            SpinBox
            {
                id: control
                implicitHeight: 48
                activeFocusOnTab: true
                value: textInp.text
                from: min
                to: max
                editable: true
                stepSize: 1
                onValueModified:
                {
                    slider.value = control.value;
                    root.update();
                }
                contentItem:TextField
                {
                    id: textInp
                    z: 2
                    text: control.value
                    color: "#243956"
                    horizontalAlignment: Qt.AlignHCenter
                    verticalAlignment: Qt.AlignVCenter
                    font.bold: true
                    font.pixelSize: 20
                    activeFocusOnTab: true
                    validator: IntValidator {bottom: min; top: max;}
                    inputMethodHints: Qt.ImhFormattedNumbersOnly
                    background: Rectangle
                    {
                        id: rect
                        color: "transparent"
                    }
                }

                up.indicator: Rectangle
                {
                    radius: 8
                    implicitHeight: control.height
                    color: "#7799c6"
                    x: parent.width - width
                    implicitWidth: 40
                    Text
                    {
                       text: "+"
                       color: "#243956"
                       font.bold: true
                       font.pixelSize: textInp.font.pixelSize
                       anchors.fill: parent
                       fontSizeMode: Text.Fit
                       horizontalAlignment: Text.AlignHCenter
                       verticalAlignment: Text.AlignVCenter
                    }
                }

                down.indicator: Rectangle
                {
                    x: 0
                    implicitWidth: 40
                    implicitHeight: control.height
                    radius: 8
                    color: "#7799c6"
                    Text
                    {
                        text: "-"
                        color: "#243956"
                        font.bold: true
                        font.pixelSize: textInp.font.pixelSize
                        anchors.fill: parent
                        fontSizeMode: Text.Fit
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                    }
                }
            }
        }
        Item{Layout.fillHeight: true}
        Slider
        {
            id: slider
            stepSize: 1
            Layout.fillWidth: true
            from: min
            to: max
            height: 17
            snapMode: Slider.SnapAlways
            activeFocusOnTab: false

            onMoved:
            {
                control.value = slider.value;
                root.update();
            }
        }
    }

    Component.onCompleted:
    {
        control.value = init_value;
        slider.value  = init_value;
    }
}
