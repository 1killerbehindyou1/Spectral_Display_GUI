import QtQuick 2.15
import QtQuick.Controls 2.15

MenuBar
{
    id: root
    property alias showSelectedImage: showSelectedImage
    property alias showRenderedPreview: showRenderedPreview
    signal resetSettingsRequested()
    property string configFolderUrl: settings_manager ? settings_manager.settingsFolderUrl : ""

    contentWidth: parent ? parent.width : implicitWidth

    Menu
    {
        title: qsTr("&File")
        Action
        {
            text: qsTr("&Utwórz projekt")
            onTriggered:
            {
                file_operation = "create_project";
                fileDialog.title = "Wybierz katalog dla nowego projektu";
                fileDialog.nameFilters = [ "All files (*)" ];
                fileDialog.selectExisting = true;
                fileDialog.selectFolder = true;
                fileDialog.folder = settings_manager ? settings_manager.projectRootUrl : "";
                fileDialog.open();
            }
        }
        MenuSeparator { }
        Action
        {
            text: qsTr("&Load Image...")
            onTriggered:
            {
                file_operation = "load";
                fileDialog.title = "Please choose a file";
                fileDialog.nameFilters = [ "Image files (*.jpg *.png)", "All files (*)" ];
                fileDialog.selectExisting = true;
                fileDialog.selectFolder = false;
                fileDialog.folder = settings_manager ? settings_manager.sourceImagesFolderUrl : "";
                fileDialog.open();
            }
        }
        MenuSeparator { }
        Action
        {
            text: qsTr("&Save Transformated Image...")
            onTriggered:
            {
                file_operation = "save";
                fileDialog.title = "Save to file";
                fileDialog.nameFilters = [ "Image files (*.jpg *.png)" ];
                fileDialog.selectExisting = false;
                fileDialog.selectFolder = false;
                fileDialog.folder = settings_manager ? settings_manager.transformedImagesFolderUrl : "";
                fileDialog.open();
            }
        }
        MenuSeparator { }
        Action
        {
            text: qsTr("&Import Settings...")
            onTriggered:
            {
                file_operation = "settings_import";
                fileDialog.title = "Import settings from JSON";
                fileDialog.nameFilters = [ "JSON files (*.json)", "All files (*)" ];
                fileDialog.selectExisting = true;
                fileDialog.selectFolder = false;
                fileDialog.folder = root.configFolderUrl;
                fileDialog.open();
            }
        }
        Action
        {
            text: qsTr("&Export Settings...")
            onTriggered:
            {
                file_operation = "settings_export";
                fileDialog.title = "Export settings to JSON";
                fileDialog.nameFilters = [ "JSON files (*.json)", "All files (*)" ];
                fileDialog.selectExisting = false;
                fileDialog.selectFolder = false;
                fileDialog.folder = root.configFolderUrl;
                fileDialog.open();
            }
        }
        MenuSeparator { }
        Action
        {
            text: qsTr("&Reset Settings to Defaults")
            onTriggered: root.resetSettingsRequested()
        }
    }

    Menu
    {
        title: qsTr("&View")
        delegate: CheckBox{}

        Action
        {
            id: showSelectedImage
            checked: false
            checkable: true
            text: "Preview selected image..."
        }

        Action
        {
            id: showRenderedPreview
            text: "Preview rendered image..."
            checked: false
            checkable: true
        }
    }
}