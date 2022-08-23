import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
 Item
{   
    id: root
    property alias text: t_field.text
    signal pressed() 
    implicitWidth: 70
    implicitHeight: 50 

    Rectangle{ radius: 4; anchors.fill: parent
            id: rect
            focus: true
            color: focus ? "lightgrey": "darkgrey" 
            MouseArea{ hoverEnabled: false; anchors.fill: parent
                        onClicked: 
                        {
                            root.pressed()
                        }
                    }
            Text{ font.pixelSize: 30;  id: t_field; text:""}
            }
}

