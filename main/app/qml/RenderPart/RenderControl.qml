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

    signal parameterChanged(int size, int rotation , int number_of_leds)

    function onUpdate()
    {
        if (transform_engine)
        {
            transform_engine.updateTransformParameters(l_num.value, l_rotation.value, l_size.value);
        }
        return root.parameterChanged(l_size.value, l_rotation.value, l_num.value )
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
            title: qsTr("Rendering Parameters")

             font.pixelSize: 15
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop

            contentItem: ColumnLayout
            {
                spacing: 20
                Layout.alignment: Qt.AlignTop

                DataInput{ id: l_num; label: "number of LEDs"; init_value: 25;  max: 200; min: 1}
                DataInput{ id: l_rotation; label:"LED angle"; init_value: 5;  max: 360; min: 1}
                DataInput{ id: l_size; label:"LED size"; init_value: 5;  max: 360; min: 1}

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
            FillingRect{Layout.fillHeight: true}


            Text{text: "Transformed image size: "; font.bold: true; font.pixelSize: 18 }
            Separator{Layout.fillWidth: true}
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
            FillingRect{fillerHeight: 100}
        }
    }


    Component.onCompleted:
    {
        l_num.update.connect(onUpdate);
        l_rotation.update.connect(onUpdate);
        l_size.update.connect(onUpdate);
        root.parameterChanged(l_size.init_value, l_rotation.init_value, l_num.init_value);
        if (transform_engine)
        {
            transform_engine.updateTransformParameters(l_num.init_value, l_rotation.init_value, l_size.init_value);
        }
    }
}




