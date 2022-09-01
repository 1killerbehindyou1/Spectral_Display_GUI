import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Main 1.0

Window 
{
    width: 1500
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "lightgrey"
    maximumHeight: 600; 
    minimumHeight: 600; 
    maximumWidth: 1500; 
    minimumWidth: 1500

    Item
    { 
        id: background
        anchors.fill: parent

        RowLayout
        { 
            id: main_row; 
            spacing: 30; 
            x: 30; 
            y:30

            Rectangle
            { 
                id: draw_area; 
                width: 600; 
                height: 520; 
                color: "white"
                    
                MouseArea
                {
                    anchors.fill: parent
                    LedRuler
                    {
                        id: led          
                        anchors.fill: parent
                        color: "blue"
                        size: 100
                        lx: 50
                        ly: 50               
                    }

                    onPressed:
                    {
                    led.matrixUpdate(mouseX - led.size/2, mouseY - led.size/2, l_rot.text);
                    }
                }               
            }
            Rectangle
            { 
                id: render_area; 
                width: 600; 
                height: 520; 
                color: "white"
            }               
        
            ColumnLayout
            { 
                id: controlColumn; 
                spacing: 10; 
                anchors.bottom: parent.bottom
                
                Button
                {
                    text: "SET"
                    onClicked: 
                    {
                        led.size = l_size.value
                        led.matrixUpdate(l_x.value, l_y.value, l_rot.value)
                    }          
                }
                    
                Text{text: "Led ruler parameters" }    
                
                        
                    DataInput{ id: l_x; value: "50"; label: "x position"}
                    DataInput{ id: l_y; value: "50"; label: "y position"}
                    DataInput{ id: l_size; value: "100"; label: "led size"}
                    DataInput{ id: l_rot; value: "0"; label: "led rotation"}                      
            }
        }
    }
}
     

