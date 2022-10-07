import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{ 
    signal fileLoadErrorInfo(string title, string name) //signal declaration

    function loadImageFromFile(filepath: url){ //global function to Draw panel object (slot)
        return picture.setPixMap(filepath);  //function set bitmap from location "filepath" return true or false
    }

    id: root
    implicitWidth: 400
    implicitHeight: 500

    background: Rectangle{ color: "white" }
    contentItem: ImageViewer 
    {
        id: picture
        anchors.fill: parent
        
        onFileErrLoad:{ root.fileLoadErrorInfo(title, name); } //emit signal aftere recevinig signag from C++ after file load error

    }
}