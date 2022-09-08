import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
 Item
{
    property alias value: textInp.text
    property alias label: label.text
    
    implicitWidth: 70
    implicitHeight: 50 
        RowLayout
        {   
            Text
            {
                id: label
                text: " "
            }   
            spacing: 10
            Rectangle
            {
                implicitWidth: 70
                implicitHeight: 50 
                id: rect
                
                TextField
                {
                    id: textInp
                    anchors.fill: parent
                    anchors.verticalCenter: rect.verticalCenter
                    text: "0"
                    color: focus ? "black" : "gray"
                    font.pixelSize: 30
                    activeFocusOnTab: true
                }   
            }    
             
        } 
                        
}       

