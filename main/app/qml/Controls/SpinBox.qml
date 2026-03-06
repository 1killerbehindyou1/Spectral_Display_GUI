import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import "." as AppControls

Controls.SpinBox
{
    id: control
    implicitHeight: 48
    activeFocusOnTab: true
    value: textInp.text
    editable: true
    stepSize: 1

    contentItem: SpixBoxText
    {
        id: textInp
        currentValue: control.value
        minValue: control.from
        maxValue: control.to
    }

    up.indicator: AppControls.Indicator
    {
        text: "+"
        implicitHeight: control.height
        textPixelSize: textInp.font.pixelSize
        x: control.width - width
    }

    down.indicator: AppControls.Indicator
    {
        text: "-"
        implicitHeight: control.height
        textPixelSize: textInp.font.pixelSize
        x: 0
    }
}
