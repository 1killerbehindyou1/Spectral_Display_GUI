import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{ 
    signal acquisitionFinished()
    
    function updateLedParameters(size: int, spacing: int, angle: int, num: int){
        
        led.number_of_leds = num;
        led.size = size;
        led.spacing = spacing;
        led.step =angle;
        return led.rulerUpdate();
        
    }

    function setAcquireStatus(status: bool)
    {
        return led.setAcquire(status)
    }

    id: root
    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }
    
    contentItem: LedRuler
    {
        id: led 
        anchors.fill: parent
        size: 10
        spacing: 5
        step: 90
        number_of_leds: 10

        onAcquisitionFinished:{ root.acquisitionFinished() }

        MouseArea{
            anchors.fill: parent
            onClicked: led.setPoint(Qt.point(mouseX, mouseY))
        }
    }                             
}