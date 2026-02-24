import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.3
import Main 1.0

Control
{
    id: root
    background: Rectangle{ color: "white" }

     function drawPreview(last_image)
     {
         return output_preview_item.drawPreview(last_image);
     }
    contentItem: OutputPreviewItem
    {
        id: output_preview_item
        anchors.fill: parent
    }
}