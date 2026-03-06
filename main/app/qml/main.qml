
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Main 1.0
import "RenderPart"
import "TransformPart"
import "MainMenu"
import "Dialogs" as AppDialogs
import "Utils"

ApplicationWindow
{
    id: root
    width: 1300
    height: 600
    visible: true
    visibility: Window.Maximized
    title: qsTr("Basic Gui")
    color: "lightgrey"

    property bool imageSelected: false
    property bool previewIsActive: mainMenu.showSelectedImage.checked
    property bool renderedPreviewIsActive: mainMenu.showRenderedPreview.checked
    property string file_operation: ""
    property point lastSelectedPoint: Qt.point(0, 0)
    property bool settingsHydrationInProgress: false
    property var drawingItem: null

    function collectCurrentState()
    {
        return
        {
            "controls":
            {
                "transform": transform_parameters.exportSettings(),
                "render": render_parameters.exportSettings()
            },
            "view":
            {
                "showSelectedImage": mainMenu.showSelectedImage.checked,
                "showRenderedPreview": mainMenu.showRenderedPreview.checked,
                "previewRotation": output_preview.previewRotation
            },
            "selection":
            {
                "pointX": Math.max(0, Math.round(lastSelectedPoint.x)),
                "pointY": Math.max(0, Math.round(lastSelectedPoint.y))
            }
        };
    }

    function buildSettingsPayload()
    {
        const defaults = settings_manager.defaultSettings();
        return
        {
            "$schema": settings_manager.schemaPath,
            "version": 1,
            "defaults": defaults.defaults,
            "current": collectCurrentState(),
            "files":
            {
                "lastLoadedFile": file_manager.lastLoadedPath ? file_manager.lastLoadedPath : "",
                "lastSavedFile": file_manager.lastSavedPath ? file_manager.lastSavedPath : ""
            }
        };
    }

    function persistSettings()
    {
        if (settingsHydrationInProgress) {
            return;
        }
        const saveOk = settings_manager.saveSettings(buildSettingsPayload());
        if (!saveOk && settings_manager.lastError)
        {
            console.warn("Failed to save settings: " + settings_manager.lastError);
        }
    }

    function scheduleSettingsSave()
    {
        if (settingsHydrationInProgress)
        {
            return;
        }
        settingsSaveTimer.restart();
    }

    function applyLoadedSettings(settings)
    {
        if (!settings || !settings.current)
        {
            return;
        }
        settingsHydrationInProgress = true;
        const current = settings.current;
        if (current.controls)
        {
            transform_parameters.applySettings(current.controls.transform);
            render_parameters.applySettings(current.controls.render);
        }
        if (current.view)
        {
            mainMenu.showSelectedImage.checked = !!current.view.showSelectedImage;
            mainMenu.showRenderedPreview.checked = !!current.view.showRenderedPreview;
            output_preview.applySettings(current.view);
        }
        if (drawingItem)
        {
            // Force deterministic animation state even if checkbox value did not change.
            drawingItem.checkRenderedPreview(mainMenu.showRenderedPreview.checked);
        }
        if (current.selection) {
            const pointX = Math.max(0, Math.round(current.selection.pointX || 0));
            const pointY = Math.max(0, Math.round(current.selection.pointY || 0));
            lastSelectedPoint = Qt.point(pointX, pointY);
        }
        if (settings.files && settings.files.lastLoadedFile) {
            const lastPath = settings.files.lastLoadedFile;
            if (file_manager.loadPixMapFromLocalPath(lastPath)) {
                selector.img_source = file_manager.toFileUrl(lastPath);
                imageSelected = true;
                output_preview.onSelectorClicked(lastSelectedPoint.x, lastSelectedPoint.y);
            }
        }
        settingsHydrationInProgress = false;
        scheduleSettingsSave();
    }

    function importSettingsFromUrl(fileUrl)
    {
        const imported = settings_manager.loadSettingsFromFile(fileUrl);
        if (settings_manager.lastError) {
            messageDialog.showMessageBox("Settings import failed", settings_manager.lastError);
            return;
        }
        applyLoadedSettings(imported);
        persistSettings();
    }

    function exportSettingsToUrl(fileUrl)
    {
        const ok = settings_manager.saveSettingsToFile(fileUrl, buildSettingsPayload());
        if (!ok) {
            const reason = settings_manager.lastError ? settings_manager.lastError : "Unknown export error.";
            messageDialog.showMessageBox("Settings export failed", reason);
        }
    }

    function resetSettingsToDefaults()
    {
        const defaults = settings_manager.defaultSettings();
        settingsHydrationInProgress = true;
        imageSelected = false;
        selector.img_source = "";
        lastSelectedPoint = Qt.point(0, 0);
        settingsHydrationInProgress = false;
        applyLoadedSettings(defaults);

        const resetPayload = {
            "$schema": settings_manager.schemaPath,
            "version": 1,
            "defaults": defaults.defaults,
            "current": defaults.current,
            "files":
            {
                "lastLoadedFile": "",
                "lastSavedFile": ""
            }
        };
        const saveOk = settings_manager.saveSettings(resetPayload);
        if (!saveOk)
        {
            const reason = settings_manager.lastError ? settings_manager.lastError : "Unknown reset error.";
            messageDialog.showMessageBox("Reset settings failed", reason);
        }
    }

    function createProjectFromUrl(folderUrl)
    {
        const ok = settings_manager.createProject(folderUrl);
        if (!ok)
        {
            const reason = settings_manager.lastError ? settings_manager.lastError : "Unknown project creation error.";
            messageDialog.showMessageBox("Create project failed", reason);
            return;
        }
        imageSelected = false;
        selector.img_source = "";
        lastSelectedPoint = Qt.point(0, 0);
        const loadedSettings = settings_manager.loadSettings();
        applyLoadedSettings(loadedSettings);
        persistSettings();
    }

    onPreviewIsActiveChanged:
    {
        selector.img_visible = imageSelected && previewIsActive;
        scheduleSettingsSave();
    }

    onRenderedPreviewIsActiveChanged: {
        if (drawingItem) {
            drawingItem.checkRenderedPreview(renderedPreviewIsActive);
        }
        scheduleSettingsSave();
    }

    onClosing: {
        persistSettings();
    }

    /* Menu Bar */
    menuBar: MainMenu
    {
        id: mainMenu
        onResetSettingsRequested: root.resetSettingsToDefaults()
    }

    RowLayout
    {
        spacing: 5
        anchors.fill: parent

        TransformControl
        {
            id: transform_parameters
            Layout.fillHeight: true
            Layout.preferredWidth: 450
            Layout.maximumWidth: 450
            visible: true
        }
        /* Parameter adjustment section */
        ColumnLayout
        {
            spacing: 5
            Layout.fillWidth: true
            Layout.fillHeight: true

            RowLayout
            {
                spacing: 5
                Layout.fillWidth: true
                Layout.fillHeight: true

                TransformSelector
                {
                    id: selector
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    visible: true
                }

                RenderPreview
                {
                    id: drawingPreview
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    visible: true
                    renderingActive: root.renderedPreviewIsActive
                    Component.onCompleted: root.drawingItem = drawingPreview
                }
            }

            TransformPreview
            {
                id: output_preview
                Layout.fillWidth: true
                Layout.alignment: Qt.AlignBottom
                Layout.preferredHeight: 200
                visible: true
            }
        }
        RenderControl
        {
            id: render_parameters
            renderingActive: root.renderedPreviewIsActive
            Layout.fillHeight: true
            Layout.preferredWidth: 350
            Layout.maximumWidth: 350
            visible: true
        }
    }

    AppDialogs.FileDialog {
        id: fileDialog
    }

    AppDialogs.MessageDialog {
        id: messageDialog
    }

    Timer
    {
        id: settingsSaveTimer
        interval: 250
        repeat: false
        onTriggered: root.persistSettings()
    }

    Component.onCompleted:
    {
        /*
        * Emit initial values so controls and engine are synchronized on startup.
        */
        transform_parameters.onRadiusUpdate();
        transform_parameters.onAngResUpdate();
        transform_parameters.onZoomLoadUpdate();
        transform_parameters.onZoomOutUpdate();
        if (drawingItem)
        {
            drawingItem.requestRepaint();
            drawingItem.checkRenderedPreview(root.renderedPreviewIsActive);
        }

        /*
        * Connect transform controls with selector and transform engine.
        */
        transform_parameters.radiusChanged.connect(selector.onRadiusChanged);
        transform_parameters.radiusChanged.connect(transform_engine.updateNoOfPixels);
        transform_parameters.angResChanged.connect(transform_engine.updateAngularResolution);
        /*
        * Connect zoom controls with input and output previews.
        */
        transform_parameters.zoomChangedLoad.connect(function (zoomFactor) {
                selector.zoomFactor = zoomFactor;
            });
        transform_parameters.zoomChangedOut.connect(function (zoomFactor) {
                output_preview.zoomFactor = zoomFactor;
            });

        /*
        * Connect file metadata and selector clicks to preview updates.
        */
        file_manager.fileLoadedSize.connect(transform_parameters.onImgLoad);
        file_manager.fileErrLoad.connect(messageDialog.showMessageBox);
        selector.pointUpdate.connect(function (xPosition, yPosition) {
                root.lastSelectedPoint = Qt.point(xPosition, yPosition);
                output_preview.onSelectorClicked(xPosition, yPosition);
                root.scheduleSettingsSave();
            });

        if (drawingItem)
        {
            render_parameters.ledNumChanged.connect(drawingItem.onLedNumChanged);
            render_parameters.ledRotationChanged.connect(drawingItem.onAngularResolutionChanged);
            render_parameters.ledSizeChanged.connect(drawingItem.onLedSizeChanged);
            render_parameters.ledDistanceChanged.connect(drawingItem.onLedDistanceChanged);
            render_parameters.ledRotationSpeedChanged.connect(drawingItem.onRotationSpeedChanged);
        }

        transform_parameters.radiusChanged.connect(root.scheduleSettingsSave);
        transform_parameters.angResChanged.connect(root.scheduleSettingsSave);
        transform_parameters.zoomChangedLoad.connect(root.scheduleSettingsSave);
        transform_parameters.zoomChangedOut.connect(root.scheduleSettingsSave);
        render_parameters.ledNumChanged.connect(root.scheduleSettingsSave);
        render_parameters.ledRotationChanged.connect(root.scheduleSettingsSave);
        render_parameters.ledSizeChanged.connect(root.scheduleSettingsSave);
        render_parameters.ledDistanceChanged.connect(root.scheduleSettingsSave);
        render_parameters.ledRotationSpeedChanged.connect(root.scheduleSettingsSave);

        render_parameters.startRenderingRequested.connect(function () {
                mainMenu.showRenderedPreview.checked = true;
            });
        render_parameters.stopRenderingRequested.connect(function () {
                mainMenu.showRenderedPreview.checked = false;
            });
        output_preview.previewRotationChanged.connect(root.scheduleSettingsSave);
        file_manager.lastLoadedPathChanged.connect(root.scheduleSettingsSave);
        file_manager.lastSavedPathChanged.connect(root.scheduleSettingsSave);
        const loadedSettings = settings_manager.loadSettings();

        if (settings_manager.lastError)
        {
            console.warn("Settings load issue: " + settings_manager.lastError);
        }
        applyLoadedSettings(loadedSettings);
    }
}
