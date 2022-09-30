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

    function updatePolygon(angle: int, point: Qt.point, size: int){
        
        return poly.polygonUpdate(angle, point, size);
    }

    id: root
    implicitWidth: 720
    implicitHeight: 500

    background: Rectangle{ color: "white" }
    
    contentItem: T_Polygon
    {
        id: poly 
        anchors.fill: parent
          //a: Qt.point(50, 50)
          //b: Qt.point(40, 180)
         // c: Qt.point(130, 250)
         // d: Qt.point(300, 300)

        onFileErrLoad:{ root.fileLoadErrorInfo(title, name); }
    }                             
}