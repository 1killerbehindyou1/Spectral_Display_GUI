import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    signal clickedButton
    property alias l_size: l_size.value
    property alias l_rot: l_rot.value

    implicitWidth: 180
    implicitHeight: 500

    padding: 10
    background: Rectangle
    {
        color: "#BBB"
    }
    
   // onRulerUpdateSignal:
    //{
        //led.size = l_size.value
        //led.rulerUpdate(l_x.value, l_y.value, l_rot.value)
        //l_size.value = 50
    //}
    contentItem: ColumnLayout
    { 
        spacing: 10; 

        ColumnLayout
        {   
            anchors.bottom: button_.top
            anchors.bottomMargin: 10

            Text{text: "Led ruler parameters" }         
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
            
                led.rulerUpdate(l_x.value, l_y.value, l_rot.value)
            
            }          
        }
                            
    }
}

       
    
    
   