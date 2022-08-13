import QtQuick 2.15
import QtQuick.Controls 2.15

Item
{

    property int led_ruler_lenght: 5
    property int led_size: 50
    property int led_ruler_spacing: 3
    //property int led_ruler_color: "red"
    
    Rectangle
    {
        
        Rectangle
        {
            id: led_ruler //anchors.fill: children
            x: 150
            y: 150
            width: 50
            height: 400
            rotation: 135
            //x: main_rect.x + main_rect.width/2 - led_size/2
            //y: main_rect.y + main_rect.height/2 - led_size/2
            
        
            Column
            {    spacing: led_ruler_spacing
                
                Repeater{   
                    model: led_ruler_lenght -1
                    delegate: Rectangle{
                        width:led_size; 
                        height: led_size
                        color: "red"
                    }
                } 
                Rectangle{ id: rED_LED1

                        color:  "red"
                        width: led_size
                        height: led_size
                        }
                Rectangle{ id: rED_LED2

                        color:  "red"
                        width: led_size
                        height: led_size
                        }
                Rectangle{ id: rED_LED3

                        color:  "red"
                        width: led_size
                        height: led_size
                        }
                Rectangle{ id: rED_LED4
                        color:  "red"
                        width: led_size
                        height: led_size
                        }
            }
        }
           
    }
    
}

//////////////////////////////////////////////////////////////////////////////////////
//generacja szachownicy
/*Grid
        {
            id: grid_l
            x: 20; y: 20
            rows: bitmap_resolution; columns: bitmap_resolution
            spacing: bitmap_grid_spacing

            Repeater{
                model: bitmap_resolution * bitmap_resolution 
                delegate: Rectangle{
                    id: rep_pix
                    width:bitmap_pixel_size; height: bitmap_pixel_size
                    color: model.index %2 ? "white" : "black"
                                 }       
                     }
        }*/

///////////////////////////////////////////////////////////////////////////////////