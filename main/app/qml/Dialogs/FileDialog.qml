import QtQuick 2.15
import QtQuick.Dialogs 1.3 as QtDialogs

Item
{
    id: dialogBridge

    property string title: ""
    property var nameFilters: []
    property bool selectExisting: true
    property bool selectFolder: false
    property url folder: ""
    property var dialogInstance: null

    function open()
    {
        if (dialogInstance)
        {
            dialogInstance.destroy();
            dialogInstance = null;
        }

        dialogInstance = fileDialogComponent.createObject(null,
        {
            title: dialogBridge.title,
            nameFilters: dialogBridge.nameFilters,
            selectExisting: dialogBridge.selectExisting,
            selectFolder: dialogBridge.selectFolder,
            folder: dialogBridge.folder,
            visible: false
        });

        if (dialogInstance)
        {
            dialogInstance.open();
        }
    }

    function close()
    {
        if (dialogInstance)
        {
            dialogInstance.close();
        }
    }

    function handleAccepted(fileUrl)
    {
        if((file_operation == "load")&&(file_manager.loadPixMap(fileUrl)))
        {
            selector.img_source = fileUrl;
            imageSelected = true;
        }
        if(file_operation == "save")
        {
            const outImage = (drawingItem && typeof drawingItem.getOutImage === "function")
                             ? drawingItem.getOutImage()
                             : (transform_engine ? transform_engine.transformedImage : null);
            file_manager.savePixMap(fileUrl, outImage);
        }
        if(file_operation == "settings_import")
        {
            root.importSettingsFromUrl(fileUrl);
        }
        if(file_operation == "settings_export")
        {
            root.exportSettingsToUrl(fileUrl);
        }
        if(file_operation == "create_project")
        {
            root.createProjectFromUrl(fileUrl);
        }
    }

    Component
    {
        id: fileDialogComponent

        QtDialogs.FileDialog
        {
            onAccepted:
            {
                dialogBridge.handleAccepted(fileUrl)
                close()
            }

            onRejected:
            {
                close()
            }

            Component.onDestruction:
            {
                if (dialogBridge.dialogInstance === this)
                {
                    dialogBridge.dialogInstance = null;
                }
            }
        }
    }

}