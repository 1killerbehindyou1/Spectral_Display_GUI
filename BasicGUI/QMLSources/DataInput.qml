import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Control
{
   id: root
    property alias label: label.text
    property int min
    property int max
    property int init_value
    
    signal update()
    
    implicitWidth: 270
    implicitHeight: 80 
         
    contentItem: ColumnLayout
    {
        spacing: 10
        RowLayout
        {       
            Layout.fillWidth: true 
            Text
            { 
                font.pixelSize: 20
                id: label 
            }    
            Item{Layout.fillWidth: true}
            SpinBox 
            {
                id: control
                //Layout.alignment: Qt.AlignRight
                activeFocusOnTab: true
                value: textInp.text
                from: min
                to: max
                editable: true
                stepSize: 1
                onValueModified:
                {
                    slider.value = control.value;
                    //root.update();
                }   
                contentItem:TextField
                {
                    id: textInp
                    text: control.value
                    color: "#243956"
                    activeFocusOnTab: true
                    background: Rectangle
                    {
                        //implicitWidth: 30
                        //implicitHeight: 20 
                        color: "red"
                    }
                    font{bold: true; pixelSize: 20}
                }
                up.indicator: Rectangle 
                {
                    x: parent.width - width
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                }
                
                down.indicator: Rectangle 
                {
                    id: down
                    height: parent.height
                    implicitWidth: 40
                    implicitHeight: 40
                }
            }
        }  
        Slider 
        {
            id: slider 
            stepSize: 1
            Layout.fillWidth: true
            from: min
            to: max
            implicitHeight: 20 
            snapMode: Slider.SnapAlways
            activeFocusOnTab: false
            
            onMoved: 
            {
                control.value = slider.value;
                //root.update();
            }
        }            
    }    
        
    Component.onCompleted:
    {
        control.value = init_value;
        slider.value  = init_value;
    }  
}       
