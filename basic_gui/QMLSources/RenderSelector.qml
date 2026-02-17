import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    signal pointUpdate(point point)

    function selectorSizeChanged(radius: int)
    {
        return selector_local.selectorUpdate(radius);
    }

    property alias img_visible: loaded_image.visible
    property alias img_source:  loaded_image.source

    onImg_sourceChanged:
    {
        console.log(loaded_image.width, loaded_image.height)
        root.width = loaded_image.width;
        root.height= loaded_image.height;
    }

    id: root
    implicitWidth: 500
    implicitHeight: 500


    background: Image
    {
        id: loaded_image
        visible: true
        fillMode: Image.PreserveAspectCrop
    }
    Selector
    {
        id: selector_local
        anchors.fill: parent
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                selector_local.setPoint(Qt.point(mouseX, mouseY));
                root.pointUpdate(Qt.point(mouseX, mouseY));
            }
        }
    }
}

