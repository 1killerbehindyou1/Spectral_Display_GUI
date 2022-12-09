import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{   
    signal parameterChanged(int size, int rotation , int number_of_leds);
    

    function onnUpdate()
    {
        root.parameterChanged(l_size.value, l_rotation.value, l_num.value )  
    }

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
                DataInput{ id: l_num; label: "led number  ";init_value: 25;  max: 50; min: 1}
                DataInput{ id: l_size; label: "led size       ";init_value: 10;  max: 20; min: 1}
                DataInput{ id: l_rotation; label:"led angle     ";init_value: 90;  max: 360; min: 1}      
                Item { Layout.fillHeight: true }
            }
            Component.onCompleted: 
            {   
               
                root.onnUpdate.connect(l_num.update);  
                root.onnUpdate.connect(l_size.update); 
                root.onnUpdate.connect(l_rotation.update);  
                root.parameterChanged(l_size.value, l_rotation.value, l_num.value );
            }
                
        }                        
    }


}

       
    
    
   