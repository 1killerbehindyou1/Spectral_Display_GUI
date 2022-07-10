import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Main 1.0

Window 
{
    width: 1000
    height: 680
    visible: true
    title: qsTr("Hello World")
    color: "lightgrey"
    maximumHeight: 680
    minimumHeight: 680
    maximumWidth: 900
    minimumWidth: 900
    //color: Qt.rgba(2,200,195,1)
    Item 
    {
        id: background
        anchors.fill: parent
                 
        Rectangle
        {
            id: draw_area
            anchors
            {
                top: background.top
                bottom: background.bottom
                left: background.left
                right: controlColumn.left
                topMargin: 30
                bottomMargin: 30
                leftMargin: 30
                rightMargin: 30
            }

            color: "white"
            Plot
            {
                 first_field_r: led_R1.text
                 first_field_g: led_G1.text
                 first_field_b: led_B1.text
                
                 second_field_r: led_R2.text
                 second_field_g: led_G2.text
                 second_field_b: led_B2.text

                 third_field_r: led_R3.text
                third_field_g: led_G3.text
                 third_field_b: led_B3.text
              
                 fourth_field_r: led_R4.text
                 fourth_field_g: led_G4.text
                 fourth_field_b: led_B4.text
              
              
            }  
                          
        }

           
        Column
        {      
            id: controlColumn
            anchors
            {
                //left: draw_area.right
                right: background.right
                bottom: background.bottom
                // top: background.top
                bottomMargin: 50
                leftMargin: 50
                rightMargin: 50
                topMargin: 50
            }
            
            spacing: 10
             Row
                {
                    anchors
                    {
                        right: background.right
                        left: draw_area.right
                        leftMargin: 50
                        rightMargin: 50
                        bottomMargin: 300
                    }
                        spacing: 10

                    Data_Input
                    {
                        id: led_R4
                        text: "0"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: led_G4
                        text: "0"
                        width: 100
                        height: 50
                    }
                     Data_Input
                    {
                        id: led_B4
                        text: "0"
                        width: 100
                        height: 50
                    }

                }
                 Row
                {
                    anchors
                    {
                        right: background.right
                        left: draw_area.right
                        leftMargin: 50
                        rightMargin: 50
                        bottomMargin: 300
                    }
                        spacing: 10

                    Data_Input
                    {
                        id: led_R3
                        text: "0"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: led_G3
                        text: "0"
                        width: 100
                        height: 50
                    }
                     Data_Input
                    {
                        id: led_B3
                        text: "0"
                        width: 100
                        height: 50
                    }

                }
            Row
                {
                    anchors
                    {
                        right: background.right
                        left: draw_area.right
                        leftMargin: 50
                        rightMargin: 50
                        bottomMargin: 300
                    }
                        spacing: 10

                    Data_Input
                    {
                        id: led_R1
                        text: "0"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: led_G1
                        text: "0"
                        width: 100
                        height: 50
                    }
                     Data_Input
                    {
                        id: led_B1
                        text: "0"
                        width: 100
                        height: 50
                    }

                }
                Row
                {
                    anchors
                    {
                        right: background.right
                        left: draw_area.right
                        leftMargin: 50
                        rightMargin: 50
                        bottomMargin: 300
                    }
                        spacing: 10

                    Data_Input
                    {
                        id: led_R2
                        text: "0"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: led_G2
                        text: "0"
                        width: 100
                        height: 50
                    }
                     Data_Input
                    {
                        id: led_B2
                        text: "0"
                        width: 100
                        height: 50
                    }

                }
                Text
                {
                    id: text_tester
                    text: "Color tester"
                }
                
                Rectangle 
                {

                    anchors
                    {
                        
                        right: parent.right
                        left: parent.left 
                    }
                    
                    color: "#" + rVal.value + gVal.value + bVal.value
                    
                    height: 50
                }

                Text
                {
                    id: label2
                    text: "#" + rVal.value + gVal.value + bVal.value
                }
                Row
                {
                    id: rgb_val
                    anchors
                    {
                        right: background.right
                        bottom: background.bottom
                        left: draw_area.right
                        leftMargin: 50
                        rightMargin: 50
                        bottomMargin: 50
                    }
                        spacing: 10

                        Data_Input
                    {
                        id: rVal
                        text: "ff"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: gVal
                        text: "00"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: bVal
                        text: "ff"
                        width: 70
                        height: 50
                    }

                }
        }
        
    } 
    
} 

//==============JAVA SCRIPT===================//
/*
fuction foo(){
    console.log("hello world", x)
    return x *2
}
*/
//============================================//


 