import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
 Item
{
    property alias text: textInp.text
    property string value: textInp.text
    //rect.implicitWidth: 100
    //rect.implicitHeight: 50 

    Rectangle
    {
        id: rect
        border.color: "black"
        border.width: 4
        color: "white"
        radius: 4
        width: 70
        height: 50

        TextInput
        {
            id: textInp
            anchors.leftMargin: 5
            anchors.margins: 2
            text: ""
            color: focus ? "black" : "gray"
            font.pixelSize: 40
            activeFocusOnTab: true
        }                                       
    }
}       

//==============JAVA SCRIPT===================//
/*
fuction foo(){
    console.log(textInp.width)
    //return textInp.width
}
*/
//============================================//