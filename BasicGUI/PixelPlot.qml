import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{

    property int led_ruler_lenght: 5
    property int led_size: 50
    property int led_ruler_spacing: 3
    //property int led_ruler_color: "red"
    
    Rectangle
    {
        
            id: led_pixel //anchors.fill: children
            x: 150
            y: 150
            width: 50
            height: 50
            rotation: 135
            color: "red"
           
    }
    
}

