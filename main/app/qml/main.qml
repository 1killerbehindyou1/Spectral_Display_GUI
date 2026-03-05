import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3
import Main 1.0
import "RenderPart"
import "TransformPart"
import "MainMenu"
import "Dialogs" as AppDialogs

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

    onPreviewIsActiveChanged: selector.img_visible = imageSelected && previewIsActive;
    onRenderedPreviewIsActiveChanged: drawing.checkRenderedPreview(renderedPreviewIsActive);

    /* Menu Bar */
    menuBar: MainMenu
    {
        id: mainMenu
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
                    id: drawing
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    visible: true
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
            Layout.fillHeight: true
            Layout.preferredWidth: 350
            Layout.maximumWidth: 350
            visible: true
        }
    }

    AppDialogs.FileDialog
    {
        id: fileDialog
    }

    AppDialogs.MessageDialog
    {
        id: messageDialog
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

        /*
        * Connect transform controls with selector and transform engine.
        */
        transform_parameters.radiusChanged.connect(selector.onRadiusChanged);
        transform_parameters.radiusChanged.connect(transform_engine.updateNoOfPixels);
        transform_parameters.angResChanged.connect(transform_engine.updateAngularResolution);
         /*
        * Connect zoom controls with input and output previews.
        */
        transform_parameters.zoomChangedLoad.connect(function(zoomFactor)
        {
            selector.zoomFactor = zoomFactor;
        });
        transform_parameters.zoomChangedOut.connect(function(zoomFactor)
        {
            output_preview.zoomFactor = zoomFactor;
        });

        /*
        * Connect file metadata and selector clicks to preview updates.
        */
        file_manager.fileLoadedSize.connect(transform_parameters.onImgLoad);
        selector.pointUpdate.connect(output_preview.onSelectorClicked);

        render_parameters.ledNumChanged.connect(drawing.onLedNumChanged);
        render_parameters.ledRotationChanged.connect(drawing.onAngularResolutionChanged);
        render_parameters.ledSizeChanged.connect(drawing.onLedSizeChanged);
        render_parameters.ledDistanceChanged.connect(drawing.onLedDistanceChanged);

    }
}


