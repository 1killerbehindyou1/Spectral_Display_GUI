import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{   
    signal newParameters(int size, int spacing, int step, int number_of_leds)

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
            ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
            ScrollBar.vertical.policy: ScrollBar.AlwaysOn
            Layout.fillHeight: true
            Layout.fillWidth: true
            clip: true

            ColumnLayout
            {
                width: parent.width
                Text{text: "Led ruler parameters" }         
                DataInput{ id: l_num; value: "10"; label: "led number  "}
                DataInput{ id: l_size; value: "10"; label: "led size       "}
                DataInput{ id: l_spacing; value: "2"; label: "led spacing  "}
                DataInput{ id: l_step; value: "90"; label:"led angle     "}      
                Item { Layout.fillHeight: true }
                         
                Button
                {
                    id: button_
                    Layout.alignment: Qt.AlignHCenter
                    text: "SET"
                    highlighted: true

                    onClicked: 
                    {
                       root.newParameters(l_size.value, l_spacing.value, l_step.value, l_num.value)
                    }          
                }
            }
        }                        
    }
}

       
    
    
   