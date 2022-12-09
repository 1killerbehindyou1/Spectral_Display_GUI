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
    
    signal update()//slider value changed

    implicitWidth: 70
    implicitHeight: 50 
    
    ColumnLayout
    {
        Text{ id: label }
            
            RowLayout
            {   
                Slider 
                {
                    id: slider 
                    stepSize: 1
                    snapMode: Slider.SnapAlways
                                  
                    onMoved: 
                    {
                        root.update();
                        textInp.text = slider.value;
                    }
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
                        color: "black" 
                        font.pixelSize: 16
                        activeFocusOnTab: true
                    }   
                }         
            }   
        }
        Component.onCompleted:
        {
           value = init_value;
        }
                   
}       
