import QtQuick 2.15
import QtQuick.Controls 2.15 as Controls
import QtQuick.Layouts 1.3

Controls.Slider
{
    id: root
    property var targetControl
    signal updateRequested()

    stepSize: 1
    Layout.fillWidth: true
    height: 17
    snapMode: Controls.Slider.SnapAlways
    activeFocusOnTab: false
    onMoved:
    {
        if (targetControl) {
            targetControl.value = root.value;
        }
        updateRequested();
    }
}
