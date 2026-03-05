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

    signal zoomChangedLoad(real zoomFactor)
    signal zoomChangedOut(real zoomFactor)
    signal radiusChanged(int radius)
    signal angResChanged(int angRes)

    function clampInt(value, minValue, maxValue)
    {
        return Math.max(minValue, Math.min(maxValue, parseInt(value)));
    }

    function exportSettings()
    {
        return {
            radius: l_radius.value,
            angularResolution: ang_res.value,
            loadZoom: l_load_zoom.value,
            outputZoom: l_out_zoom.value
        };
    }

    function applySettings(settings)
    {
        if (!settings)
        {
            return;
        }

        l_radius.setCurrentValue(
            clampInt(settings.radius !== undefined ? settings.radius : l_radius.init_value,
                     l_radius.min, l_radius.max));
        ang_res.setCurrentValue(
            clampInt(settings.angularResolution !== undefined ? settings.angularResolution : ang_res.init_value,
                     ang_res.min, ang_res.max));
        l_load_zoom.setCurrentValue(
            clampInt(settings.loadZoom !== undefined ? settings.loadZoom : l_load_zoom.init_value,
                     l_load_zoom.min, l_load_zoom.max));
        l_out_zoom.setCurrentValue(
            clampInt(settings.outputZoom !== undefined ? settings.outputZoom : l_out_zoom.init_value,
                     l_out_zoom.min, l_out_zoom.max));

        onRadiusUpdate();
        onAngResUpdate();
        onZoomLoadUpdate();
        onZoomOutUpdate();
    }

    function onRadiusUpdate()
    {
        console.log("radius changed: " + l_radius.value);
        root.radiusChanged(l_radius.value);
    }
    function onZoomOutUpdate()
    {
        console.log("zoom changed: " + l_out_zoom.value);
        root.zoomChangedOut(l_out_zoom.value);
    }

    function onZoomLoadUpdate()
    {
        console.log("zoom changed: " + l_load_zoom.value);
        root.zoomChangedLoad(l_load_zoom.value);
    }

    function onAngResUpdate()
    {
        console.log("angular resolution changed: " + ang_res.value);
        root.angResChanged(ang_res.value);
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
             title: "Selector radius"
             font.pixelSize: 18
             font.bold: true
             Layout.fillWidth: true
             Layout.preferredHeight: parent.height
             Layout.preferredWidth: parent.width
             Layout.alignment: Qt.AlignTop


            contentItem: ColumnLayout
            {
                spacing: 20
                DataInput{ id: l_radius; label: "Radius in pixels:"; init_value: 100;  max: 240; min: 1}
                DataInput{ id: ang_res; label: "Angular resolution [°]: "; init_value: 1;  max: 360; min: 1}
                FillingRect{Layout.fillHeight: true}

                Text{text: "Size of loaded img [pixels]: "; font.bold: true; font.pixelSize: 18 }
                Text{id: loadedImgSizeText; text: "0 x 0"; font.pixelSize: 18 }
                Text{text: "Loaded img preview zoom"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_load_zoom; label: "Zoom [x]: "; init_value: 1; max: 10; min: 1 }
                Separator{Layout.fillWidth: true}

                Text{text: "Output preview zoom"; font.bold: true; font.pixelSize: 18 }
                DataInput{ id: l_out_zoom; label: "Zoom [x]: "; init_value: 3; max: 10; min: 1 }
                Separator{Layout.fillWidth: true}

                Text{text: "Transformed image size: "; font.bold: true; font.pixelSize: 18 }
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
            FillingRect{fillerHeight: 20}
        }
    }

    Component.onCompleted:
    {

        l_load_zoom.update.connect(onZoomLoadUpdate);
        l_out_zoom.update.connect(onZoomOutUpdate);
        l_radius.update.connect(onRadiusUpdate);
        ang_res.update.connect(onAngResUpdate);

        root.zoomChangedLoad(l_load_zoom.init_value);
        root.zoomChangedOut(l_out_zoom.init_value);
        root.radiusChanged(l_radius.init_value);
        root.angResChanged(ang_res.init_value);
    }
}




