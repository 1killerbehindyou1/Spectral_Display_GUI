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
            spacing: 10
            Rectangle
            {
                implicitWidth: 70
                implicitHeight: 50 
                id: rect
                //anchors.fill: parent
                border.color: "black"
                border.width: 4
                color: "white"
                radius: 4
                TextInput 
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
            Text
            {
                id: label
                text: " "
            }    
        } 
                        
}       

