import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{
    property int rotation: 10

    property real first_field: ((dragSquare.width - (dragSquare.x - first_square.x)) *(dragSquare.width - (dragSquare.y - first_square.y)))/ (dragSquare.width*dragSquare.width)
    property real first_field_r: 1.0
    property real first_field_g: 0.0
    property real first_field_b: 0.0
    
    property real second_field:  ((dragSquare.width - (second_square.x - dragSquare.x)) *(dragSquare.width - (dragSquare.y - second_square.y))) / (dragSquare.width*dragSquare.width)
    property real second_field_r: 0.0
    property real second_field_g: 0.0
    property real second_field_b: 0.5
    
    property real third_field: ((dragSquare.width - (dragSquare.x - third_square.x)) *(dragSquare.width - (third_square.y - dragSquare.y))) / (dragSquare.width*dragSquare.width) 
    property real third_field_r: 0.45
    property real third_field_g: 0.76
    property real third_field_b: 0.21
    
    property real fourth_field: ((dragSquare.width - (fourth_square.x - dragSquare.x )) *(dragSquare.width - (fourth_square.y - dragSquare.y )))/ (dragSquare.width*dragSquare.width)
    property real fourth_field_r: 0.87
    property real fourth_field_g: 0.11
    property real fourth_field_b: 0.23
    
    property real common_r: first_field * first_field_r + second_field * second_field_r + third_field * third_field_r +fourth_field * fourth_field_r
    property real common_g: first_field * first_field_g + second_field * second_field_g + third_field * third_field_g +fourth_field * fourth_field_g
    property real common_b: first_field * first_field_b + second_field * second_field_b + third_field * third_field_b +fourth_field * fourth_field_b
    
    
    Text
    {
        id: label2
        anchors.bottom: parent.bottom

        text: "red first: " + first_field + "\tsecond field: " + second_field +"\tthird field: " + third_field + "\tfourth field: " + fourth_field
 
    }

    Rectangle
    {

        id: main_rect  
        width: 400 
        height: main_rect.width  
        Rectangle
        {
            id: first_square
            x:50
            y:50
            width: main_rect.width /2
            height: main_rect.width /2
            color: Qt.rgba(first_field_r,first_field_g,first_field_b,1)
        }
        Rectangle
        {
            id: second_square
            x: 250
            y: 50
            width: main_rect.width /2
            height: main_rect.width /2
            color: Qt.rgba(second_field_r,second_field_g,second_field_b,1)
        }
        Rectangle
        {
            id: third_square
            x: 50
            y:250
            width: main_rect.width /2
            height: main_rect.width /2
            color: Qt.rgba(third_field_r,third_field_g,third_field_b,1)
        }
        Rectangle
        {
            id: fourth_square
            x: 250
            y:250
            width: main_rect.width /2
            height: main_rect.width /2
            color: Qt.rgba(fourth_field_r,fourth_field_g,fourth_field_b,1)
        }
        Rectangle
        {   
            id: dragSquare
            x:150
            y:150
            rotation: rotation
            width: 200
            height: dragSquare.width
            color: "black"
            MouseArea 
            {
                anchors.fill: parent
            //! [drag]
                drag.target: dragSquare
                drag.axis: Drag.XAndYAxis
                drag.minimumX: 50
                drag.maximumX: main_rect.width - parent.width + 50
                drag.minimumY: 50
                drag.maximumY: main_rect.height - parent.width + 50
                
            //! [drag]
                onReleased: 
                {
                // dPieChart.clearChart()
                    dragSquare.color = Qt.rgba(common_r,common_g,common_b,1)
                }
                
            }
        }
    }
}

/*vectoPlot
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

                 //rotation: 45
              
            }  */

            /*  //<===================== VectorPlot controls
                    Data_Input
                    {
                        id: rotation_c
                        text: "19"
                        width: 100
                        height: 50
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
                        id: led_R4
                        text: "1"
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
                        text: "1"
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
                        text: "1"
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
                        text: "1"
                        width: 100
                        height: 50
                    }
                    Data_Input
                    {
                        id: led_G2
                        text: "1"
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