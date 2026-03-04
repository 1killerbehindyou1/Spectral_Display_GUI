import QtQuick 2.15
import QtQuick.Dialogs 1.3 as QtDialogs

QtDialogs.FileDialog
{
    signal pixmapLoaded()

    id: fileDialog
    selectMultiple: false

    onAccepted:
    {
        if((file_operation == "load")&&(file_manager.loadPixMap(fileDialog.fileUrl)))
        {
            selector.img_source = fileDialog.fileUrl;
            imageSelected = true;
            fileDialog.pixmapLoaded();
        }
        if(file_operation == "save")
        {
            file_manager.savePixMap(fileDialog.fileUrl, drawing.getOutImage());
        }
    }

    onRejected:
    {
        fileDialog.close()
    }

    Component.onCompleted: visible = false
}