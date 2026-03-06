# Copilot Instructions for Spectral_Display_GUI

## QML Component Structure

### One component per file
Each distinct UI element **must** live in its own `.qml` file under `main/app/qml/Controls/`.
Never inline a complete sub-element inside a parent component. Instead, extract it and reference by type name.

Examples of separate files already in use:
- `SpinBox.qml` — spin box with +/- buttons
- `SpixBoxText.qml` — text input field used as SpinBox content item
- `Indicator.qml` — +/- button rectangle used as SpinBox indicator
- `Slider.qml` — slider with sync signal
- `DataInput.qml` — composite label + SpinBox + Slider

### Register every new QML file in qml.qrc
Whenever a new `.qml` file is created in `main/app/qml/`, it **must** be added to `main/app/qml/qml.qrc` before building.
Forgetting this causes `No such file or directory` errors at runtime even though the file exists on disk.

### Avoid Qt type name collisions in custom components
When a custom component file has the same base name as a Qt built-in type (e.g. `SpinBox.qml`, `Slider.qml`),
import Qt controls with an alias to avoid self-reference:

```qml
import QtQuick.Controls 2.15 as Controls
Controls.SpinBox { ... }   // Qt built-in
Controls.Slider  { ... }   // Qt built-in
```

### Import local components with `import "." as AppControls`
Use `import "." as AppControls` in any file that references sibling custom components:

```qml
import "." as AppControls
AppControls.SpinBox { ... }
AppControls.Slider  { ... }
AppControls.Indicator { ... }
```

### Expose parent-scope values as properties
When extracting a sub-element to a separate file, replace implicit references to parent `id`s
(e.g. `control.height`, `textInp.font.pixelSize`) with explicit `property` declarations and bind them at the usage site:

```qml
// Indicator.qml
Rectangle {
    property int textPixelSize: 20
    ...
}

// SpinBox.qml
AppControls.Indicator {
    textPixelSize: textInp.font.pixelSize
    implicitHeight: control.height
}
```
