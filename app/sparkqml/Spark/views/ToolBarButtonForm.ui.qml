import QtQuick 2.4
import QtQuick.Controls 2.0
import FontAwesome 1.0

MouseArea {
    id: component
    width: 32
    height: 24
    hoverEnabled: true

    property alias icon:  textItem.text
    property bool hovered: false
    property string toolTip: ""

    ToolTip.delay: 1000

    ToolTip.timeout: 5000

    ToolTip.visible: hovered && toolTip !== ""

    ToolTip.text: toolTip


    Text {
        id: textItem
        color: "#deffffff"
        font.pixelSize: 14
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        text: FontAwesome.tasks
        font.family: FontAwesome.fontFamily
    }

    states: [
        State {
            name: "Pressed"
            when: component.pressed

            PropertyChanges {
                target: mask
                visible: true
            }
        }
    ]
    Rectangle {
        id: mask
        width: 640
        height: 480
        anchors.fill: parent
        color: "white"
        opacity: 0.3
        visible: false
    }
}
