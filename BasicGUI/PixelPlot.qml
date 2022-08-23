import QtQuick 2.15
import QtQuick.Controls 2.15
//import Charts 1.0

Item
{

    //property int led_ruler_color: "red"
    
    Rectangle
    {
        /*
            id: led_pixel //anchors.fill: children
            x: 150
            y: 150
            width: 50
            height: 50
            rotation: 135
            color: "red"
           */
        LedMatrix
        {
        id: aLedMAtrix
        anchors.centerIn: parent
        width: 100; height: 100
        name: "A simple Plot"
        color: "red"
        }
    }
    
}

