import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Main 1.0

Window 
{
    width: 970
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "lightgrey"
    maximumHeight: 600; minimumHeight: 600; maximumWidth: 1000; minimumWidth: 1000


Item{ id: background; anchors.fill: parent

    Row{ id: main_row; spacing: 30; x: 30; y:30

    Rectangle{ id: draw_area; width: 600; height: 520; color: "white"
            
            MouseArea{
                anchors.fill: parent
                LedMatrix
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
        
        
     Column{ 
        id: controlColumn; spacing: 10; anchors.bottom: parent.bottom
        
               
            Button{
                    text: "SET"
                    onClicked: 
                    {
                       led.size = l_size.text

                       led.matrixUpdate(l_x.text, l_y.text, l_rot.text)
                    }          
                }
            
            Text{text: "Led ruler parameters" }    
        Row{ id: led_par; spacing: 10
                
                    DataInput{ id: l_x; text: "50"}
                    DataInput{ id: l_y; text: "50"}
                    DataInput{ id: l_size; text: "100"}
                    DataInput{ id: l_rot; text: "0"}
                }
            Text{ text: "led x   led y  led size   led rotation"}
                           
            }
    }
    }
     
} 
