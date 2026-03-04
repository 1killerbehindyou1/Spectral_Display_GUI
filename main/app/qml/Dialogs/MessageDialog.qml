import QtQuick 2.15
import QtQuick.Dialogs 1.3 as QtDialogs

QtDialogs.MessageDialog
{
    id: messageDialog
    title: ""
    text: ""

    onAccepted:
    {
        messageDialog.close()
    }

    function showMessageBox(title: string, message: string)
    {
        messageDialog.text = message
        messageDialog.title = title
        messageDialog.open()
    }
}