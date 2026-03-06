import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import "." as AppControls

Control
{
    id: root
    implicitWidth: 270

    //definitions of properties
    property alias label: label.text
    property alias value: control.value
    property int max
    property int min
    property int init_value

    //signals
    signal update

    //slots
    function setCurrentValue(newValue)
    {
        control.value = newValue;
        slider.value = newValue;
    }

   contentItem: ColumnLayout
    {
        RowLayout
        {
            Text
            {
                id: label
                font.pixelSize: 20
            }
            Item
            {
                Layout.fillWidth: true
            }

            AppControls.SpinBox
            {
                id: control
                from: min
                to: max
                onValueModified:
                {
                    slider.value = control.value;
                    root.update();
                }
            }
        }
        Item
        {
            Layout.fillHeight: true
        }
        AppControls.Slider
        {
            id: slider
            from: min
            to: max
            targetControl: control
            onUpdateRequested: root.update()
        }
    }

    //action on loaded
    Component.onCompleted:
    {
        control.value = init_value;
        slider.value = init_value;
    }
}
