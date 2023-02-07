import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    signal parameterChanged(int size, int rotation , int number_of_leds)


    function onUpdate()
    {
       return root.parameterChanged(l_size.value, l_rotation.value, l_num.value )
    }

    implicitWidth: 500
    implicitHeight: 500

    padding: 10
    background: Rectangle
    {
        color: "#c8d6e8"
    }

    /*contentItem: ColumnLayout
    {
        spacing: 10;
        ScrollView
        {
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true*/

            contentItem:ColumnLayout
            {
                spacing: 20
                Text{text: "Spectral display hardware"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_num; label: "led number";init_value: 25;  max: 200; min: 1}
                DataInput{ id: l_rotation; label:"led angle";init_value: 5;  max: 360; min: 1}
                RowLayout
                {
                    Text{text: "Spectral display resolution: "; font.pixelSize: 18 }
                    TextField
                    {
                        readOnly: true
                        text: parseInt(360/l_rotation.value) + " x " + l_num.value + " pixels";
                        color: "#243956"
                        font.pixelSize: 20
                        activeFocusOnTab: false
                        background: Rectangle {color: "transparent"}
                    }
                }

                Rectangle
                {
                    height: 1
                    border.width: 2
                    color: "black"
                    Layout.fillWidth: true
                }

                Text{text: "Selector Diameter"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_size; label: "Size [pixels]: "; init_value: 10;  max: 1000; min: 1}
                RowLayout
                {
                    Text{text: "selector in pixels: "; font.pixelSize: 18 }
                    TextField
                    {
                        readOnly: true
                        text: l_num.value * l_size.value * 2 + " pixels";
                        color: "#243956"
                        font.pixelSize: 20
                        activeFocusOnTab: false
                        background: Rectangle {color: "transparent"}
                    }
                }
            }

       // }
   // }

    Component.onCompleted:
    {
        l_num.update.connect(onUpdate);
        l_size.update.connect(onUpdate);
        l_rotation.update.connect(onUpdate);
    }
}



