import QtQuick 2.15
import QtQuick.Dialogs 1.3 as QtDialogs

QtDialogs.FileDialog
{
    id: fileDialog
    selectMultiple: false

    onAccepted:
    {
        if((file_operation == "load")&&(file_manager.loadPixMap(fileDialog.fileUrl)))
        {
            selector.img_source = fileDialog.fileUrl;
            imageSelected = true;
        }
        if(file_operation == "save")
        {
            const outImage = (drawing && typeof drawing.getOutImage === "function")
                             ? drawing.getOutImage()
                             : (transform_engine ? transform_engine.transformedImage : null);
            file_manager.savePixMap(fileDialog.fileUrl, outImage);
        }
        if(file_operation == "settings_import")
        {
            root.importSettingsFromUrl(fileDialog.fileUrl);
        }
        if(file_operation == "settings_export")
        {
            root.exportSettingsToUrl(fileDialog.fileUrl);
        }
        if(file_operation == "create_project")
        {
            root.createProjectFromUrl(fileDialog.fileUrl);
        }
    }

    onRejected:
    {
        fileDialog.close()
    }

    Component.onCompleted: visible = false
}