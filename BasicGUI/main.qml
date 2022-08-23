import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
//import Main 1.0
//import Charts 1.0

Window 
{
    width: 970
    height: 600
    visible: true
    title: qsTr("Hello World")
    color: "lightgrey"
    maximumHeight: 600; minimumHeight: 600; maximumWidth: 970; minimumWidth: 970


Item{ id: background; anchors.fill: parent

    Row{ id: main_row; spacing: 30; x: 30; y:30

    Rectangle{ id: draw_area; width: 600; height: 520; color: "white"
            
            
        
    PixelPlot{ id: p_plot}
             }
        
     Column{ id: controlColumn; spacing: 10; anchors.bottom: parent.bottom
        
                Text{text: "Matrix pixel size: \t"  + "\nm_number_of_pixels: \t"}
               
       My_button{text: "SET"
                    onPressed: 
                    {

                    }          
                }
            
            Text{text: "Led ruler parameters" }    
        Row{ id: led_par; spacing: 10
                
                    Data_Input{ id: l_spacing; text: "3"}
                    Data_Input{ id: l_size; text: "30"}
                    Data_Input{ id: l_length; text: "10"}
                }
            Text{ text: "led spacing   led size  led len"}                  
            Text{  text: "Grid parameters" }               
                
            Row{ id: grid_par; spacing: 10
                
                    Data_Input{ id: g_spacing; text: "3"}
                    Data_Input{ id: p_res; text: "7"}
                    Data_Input{ id: p_size; text: "50"}
                } 
            Text{text: "grid spacing    pixel res  pixel size"}               
            }
        }
    } 
} 

//<===============================================================================width: 100; height: 50
