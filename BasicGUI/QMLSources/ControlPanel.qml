import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{   
    signal parameterChanged(int number_of_leds, int rotation, int spacing,int size);
    property int state 

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
                DataInput{ id: l_rotation; value: "90"; label:"led angle     "}      
                Item { Layout.fillHeight: true }
                         
                Button
                {
                    id: button_
                    Layout.alignment: Qt.AlignHCenter
                    text: "SET"
                    highlighted: true

                    onClicked: 
                    {
                        root.parameterChanged(l_num.value,  l_rotation.value, l_spacing.value, l_size.value )
                    }          
                }

                Button
                {
                    id: button2
                    Layout.alignment: Qt.AlignHCenter
                    text: "SET"
                    highlighted: true

                    onClicked: 
                    {
                        console.log(root.state? "true" : "false");
                        if(root.state) root.state = false;
                        else root.state = true;
                        
                    }          
                }
            }
        }                        
    }
}

       
    
    
   