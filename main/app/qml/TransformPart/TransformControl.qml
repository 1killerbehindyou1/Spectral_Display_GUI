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

    signal zoomChanged(real zoomFactor)
    signal radiusChanged(int radius)

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

    function onImgLoad(width, height)
    {
        console.log("size of loaded image: " + width + " x " + height);
        loadedImgSizeText.text = width + " x " + height;
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
             title: qsTr("Transformation Parameters")
             font.pixelSize: 15
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop


            contentItem: ColumnLayout
            {
                spacing: 20
                FillingRect{Layout.fillWidth: true; fillerHeight: 20}
                Text{text: "Selector radius [in pixels]"; font.bold: true; font.pixelSize: 18 }
                Separator{Layout.fillWidth: true}
                DataInput{ id: l_radius; label: "Radius: "; init_value: 100;  max: 240; min: 1}

                FillingRect{Layout.fillHeight: true}
                Text{text: "Size of loaded img [pixels]: "; font.bold: true; font.pixelSize: 18 }
                Text{id: loadedImgSizeText; text: "0 x 0"; font.pixelSize: 18 }
                Text{text: "Output preview zoom"; font.bold: true; font.pixelSize: 18 }
                Separator{Layout.fillWidth: true}
                DataInput{ id: l_zoom; label: "Zoom [x]: "; init_value: 3; max: 10; min: 1 }
            }
            FillingRect{fillerHeight: 20}
        }
    }

    Component.onCompleted:
    {

        l_zoom.update.connect(onZoomUpdate);
        l_radius.update.connect(onRadiusUpdate);

        root.zoomChanged(l_zoom.init_value);
        root.radiusChanged(l_radius.init_value);
    }
}




