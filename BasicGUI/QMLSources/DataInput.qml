import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Control
{
   id: root
    property alias value: textInp.text
    property alias label: label.text
    property alias min: slider.from
    property alias max: slider.to
    property alias init_value: slider.value
    
    signal update()
    
    implicitWidth: 70
    implicitHeight: 50 
       
        ColumnLayout
        {
            RowLayout
            {        
                Text
                { 
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignRight
                    id: label 
                }    
                TextField
                {
                    id: textInp
                    text: "0"
                    color: "#243956"
                    background: Rectangle
                    {
                        implicitWidth: 70
                        implicitHeight: 30 
                        color: "transparent"
                    }
                    font
                    {   
                        bold: true
                        pixelSize: 20
                    }
                    activeFocusOnTab: true
                }
            }  
            Slider 
            {
                id: slider 
                stepSize: 1
                implicitHeight: 20 
                snapMode: Slider.SnapAlways
                                
                onMoved: 
                {
                    root.update();
                    textInp.text = slider.value;
                }
            }            
        }    
            
        
        Component.onCompleted:
        {
           value = init_value;
        }
                   
}       
