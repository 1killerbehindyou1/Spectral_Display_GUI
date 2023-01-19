import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.3

Control
{
   id: root
    property alias label: label.text
    property int min
    property int max
    property int init_value
    
    signal update()
    
    implicitWidth: 70
    implicitHeight: 50 
       
        ColumnLayout
        {
            RowLayout
            {        
                Text
                { 
                    Layout.fillWidth: true
                    Layout.alignment: Qt.AlignRight
                    id: label 
                }    
                /*TextField
                {
                    id: textInp
                    text: "0"
                    color: "#243956"
                    activeFocusOnTab: true
                    background: Rectangle
                    {
                        implicitWidth: 70
                        implicitHeight: 30 
                        color: "transparent"
                    }
                    font
                    {   
                        bold: true
                        pixelSize: 20
                    }
                    onEditingFinished:
                    {
                        slider.value = textInp.text;
                        root.update();
                    }    
                }*/
                SpinBox 
                {
                    id: textInp
                    activeFocusOnTab: true
                    value: 1
                    from: min
                    to: max
                    editable: true
                    stepSize: 1
                    onValueModified:
                    {
                        slider.value = textInp.value;
                        //root.update();
                    }   
                    //down.hovered: bool
                    //down.implicitIndicatorHeight: real
                    //down.implicitIndicatorWidth: real
                    //down.indicator: Item
                    //down.pressed: bool
                    
                   
                    //inputMethodComposing: bool
                    //inputMethodHints: flags
                    //
                    //textFromValue: function
                    //to: int
                    //up.hovered: bool
                    //up.implicitIndicatorHeight: real
                    //up.implicitIndicatorWidth: real
                    //up.indicator: Item
                    //up.pressed: bool
                    //validator: Validator
                    //value: int
                    //valueFromText: function
                    //wrap: bool
                    //valueModified()
                    //availableHeight: real
                    //availableWidth: real
                    //background: Item
                    //bottomInset: real
                    //bottomPadding: real
                    //contentItem: Item
                    //focusPolicy: enumeration
                    //focusReason: enumeration
                    //font: font
                    //horizontalPadding: real
                    //hoverEnabled: bool
                    //hovered: bool
                    //implicitBackgroundHeight: real
                    //implicitBackgroundWidth: real
                    //implicitContentHeight: real
                    //implicitContentWidth: real
                    //leftInset: real
                    //leftPadding: real
                    //locale: Locale
                    //mirrored: bool
                    //padding: real
                    //palette: palette
                    //rightInset: real
                    //rightPadding: real
                    //spacing: real
                    //topInset: real
                    //topPadding: real
                    //verticalPadding: real
                    //visualFocus: bool
                    //wheelEnabled: bool
                    //activeFocus: bool
                    //activeFocusOnTab: bool
                    //anchors.alignWhenCentered: bool
                    //anchors.baseline: AnchorLine
                    //anchors.baselineOffset: real
                    //anchors.bottom: AnchorLine
                    //anchors.bottomMargin: real
                    //anchors.centerIn: Item
                    //anchors.fill: Item
                    //anchors.horizontalCenter: AnchorLine
                    //anchors.horizontalCenterOffset: real
                    //anchors.left: AnchorLine
                    //anchors.leftMargin: real
                    //anchors.margins: real
                    //anchors.right: AnchorLine
                    //anchors.rightMargin: real
                    //anchors.top: AnchorLine
                    //anchors.topMargin: real
                    //anchors.verticalCenter: AnchorLine
                    //anchors.verticalCenterOffset: real
                    //antialiasing: bool
                    //baselineOffset: int
                    //children: list<Item>
                    //childrenRect.height: real
                    //childrenRect.width: real
                    //childrenRect.x: real
                    //childrenRect.y: real
                    //clip: bool
                    //containmentMask: QObject*
                    //data: list<Object>
                    //enabled: bool
                    //focus: bool
                    //height: real
                    //implicitHeight: real
                    //implicitWidth: real
                    //layer.effect: Component
                    //layer.enabled: bool
                    //layer.format: enumeration
                    //layer.mipmap: bool
                    //layer.samplerName: string
                    //layer.samples: enumeration
                    //layer.smooth: bool
                    //layer.sourceRect: rect
                    //layer.textureMirroring: enumeration
                    //layer.textureSize: size
                    //layer.wrapMode: enumeration
                    //opacity: real
                    //parent: Item
                    //resources: list<Object>
                    //rotation: real
                    //scale: real
                    //smooth: bool
                    //state: string
                    //states: list<State>
                    //transform: list<Transform>
                    //transformOrigin: enumeration
                    //transitions: list<Transition>
                    //visible: bool
                    //visibleChildren: list<Item>
                    //width: real
                    //x: real
                    //y: real
                    //z: real
                    //childAt()
                    //contains()
                    //forceActiveFocus()
                    //forceActiveFocus()
                    //grabToImage()
                    //mapFromGlobal()
                    //mapFromItem()
                    //mapFromItem()
                    //mapToGlobal()
                    //mapToItem()
                    //mapToItem()
                    //nextItemInFocusChain()  
                }
                
            }  
            Slider 
            {
                id: slider 
                stepSize: 1
                from: min
                to: max
                implicitHeight: 20 
                snapMode: Slider.SnapAlways
                activeFocusOnTab: false
                
                onMoved: 
                {
                    textInp.value = slider.value;
                    //root.update();
                }
            }            
        }    
            
        Component.onCompleted:
        {
           textInp.value = init_value;
           slider.value  = init_value;
        }  
}       
