import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{ 
    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle
    {
        color: "white"
    }
    contentItem: LedRuler
    {
        id: led          
        anchors.fill: parent
        color: "blue"
        size: 100
        lx: 50
        ly: 50 
        MouseArea
        {
            anchors.fill: parent
            onPressed:{led.rulerUpdate(mouseX, mouseY, l_rot.value)}
        }                 
    }

                                  
}
    
    

        