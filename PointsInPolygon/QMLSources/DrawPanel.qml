import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{ 
    signal fileLoadErrorInfo(string title, string name)

    function loadImageFromFile(filepath: url){ //global function to Draw panel object
        return poly.setPixMap(filepath);  //function set bitmap from location "filepath" return true or false
    }

    id: root
    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }
    
    contentItem: T_Polygon
    {
        id: poly 
        anchors.fill: parent
        //A: Qt.point(50,50)
        //B: Qt.point(150, 50)
        //C: Qt.point(50, 150)
       // D: Qt.point(150, 150)

        onFileErrLoad:{ root.fileLoadErrorInfo(title, name); }
    }                             
}