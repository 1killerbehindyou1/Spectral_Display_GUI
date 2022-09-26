import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{ 
    signal fileLoadErrorInfo(string title, string name)

    function updateLedParameters(size: int, spacing: int, step: int, number_of_leds: int){ //global function to Draw panel object
       
        led.number_of_leds = number_of_leds
        led.size = size;
        led.spacing = spacing;
        led.step = step;
        led.rulerUpdate(); //overloaded function used to just update view
    }

    function loadImageFromFile(filepath: url){ //global function to Draw panel object
        return led.setPixMap(filepath);  //function set bitmap from location "filepath" return true or false
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

        Component.onCompleted: 
        {
            led.rulerUpdate()
        }

        onFileErrLoad:
        {
            root.fileLoadErrorInfo(title, name)
        }
        MouseArea
        {
            id: mouse_area
            anchors.fill: parent
            onPressed:
            {
                led.setPoint(Qt.point(mouseX, mouseY))  //updating transform position
            }
        }                 
    }                             
}