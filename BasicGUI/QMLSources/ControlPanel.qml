import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Item
{
    Control
    {
        implicitWidth: 180
        implicitHeight: 500

        padding: 10
        background: Rectangle
        {
            color: "#BBB"
        }
        
        contentItem: ColumnLayout
        { 
            spacing: 10; 

            ColumnLayout
            {   
                anchors.bottom: button_.top
                anchors.bottomMargin: 10

                Text{text: "Led ruler parameters" }         
                DataInput{ id: l_x; value: "50"; label:"x position  "}
                DataInput{ id: l_y; value: "50"; label:"y position  "}
                DataInput{ id: l_size; value: "100"; label: "led size     "}
                DataInput{ id: l_rot; value: "0"; label:"led rotation"}      
            }
            
            Button
            {
                id: button_
                anchors.horizontalCenter: parent.horizontalCenter
                text: "SET"
                onClicked: 
                {
                    led.size = l_size.value
                    led.rulerUpdate(l_x.value, l_y.value, l_rot.value)
                }          
            }
                                
        }
    }
}
       
    
    
   