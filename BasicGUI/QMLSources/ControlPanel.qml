import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root

    padding: 10
    background: Rectangle
    {
        color: "#DDD"
    }
    
    contentItem: ColumnLayout
    { 
        spacing: 10; 

        ScrollView
        {
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            ColumnLayout {
                width: parent.width

                Text{ text: "Led ruler parameters" }         
                DataInput{ id: l_x; value: "50"; label:"x position"}
                DataInput{ id: l_y; value: "50"; label:"y position"}
                DataInput{ id: l_size; value: "100"; label: "led size"}
                DataInput{ id: l_rot; value: "0"; label:"led rotation"}
                Item { Layout.fillHeight: true }
            }
        }
        
        Button
        {
            id: button_
            Layout.alignment: Qt.AlignHCenter
            text: "SET"
            highlighted: true
            onClicked: 
            {
                led.size = l_size.value
                led.rulerUpdate(l_x.value, l_y.value, l_rot.value)
            }          
        }
                            
    }
}

       
    
    
   