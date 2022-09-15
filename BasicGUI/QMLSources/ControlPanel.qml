import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    padding: 10
    signal newParameters(int size, int rotation)

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
                DataInput{ id: l_size; value: "100"; label: "led size     "}
                DataInput{ id: l_rot; value: "0"; label:"led rotation"}      
                Item { Layout.fillHeight: true }
                         
                Button
                {
                    id: button_
                    Layout.alignment: Qt.AlignHCenter
                    text: "SET"
                    highlighted: true

                    onClicked: 
                    {
                        root.newParameters(l_size.value, l_rot.value)
                    }          
                }
            }
        }                        
    }
}

       
    
    
   