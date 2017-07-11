import QtQuick 2.4
import QtQuick.Layouts 1.3
import "../components"

Rectangle {
    id: component
    width: 180
    height: 190
    color: "transparent"

    property string source: ""
    property alias preview: viewer.source
    property string qml: ""
    property string ui: ""

    ColumnLayout {
        spacing: 8
        anchors.fill: parent

        Item {
            id: container
            width: component.width
            height: 140

            Card {
                width: container.width - 2
                height: container.height - 2
                anchors.centerIn: parent

                ComponentViewer {
                    id: viewer
                    anchors.fill: parent
                    asynchronous: true
                    clip: true
                }
            }
        }

        Text {
            id: text1
            color: "#de000000"
            text: component.qml
            Layout.maximumHeight: text === "" ? 0 : 14
            Layout.minimumHeight: text === "" ? 0 : 14
            verticalAlignment: Text.AlignVCenter
            Layout.fillWidth: true
            Layout.fillHeight: true
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: 14
            elide: Text.ElideMiddle
        }

        Text {
            id: text2
            color: "#de000000"
            text: component.ui
            Layout.minimumHeight: 14
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            Layout.fillHeight: true
            Layout.fillWidth: true
            font.pixelSize: 14
            elide: Text.ElideMiddle
        }

        Item {
            id: spacer
            width: 200
            height: 200
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: {
            actions.pop();
            actions.load(component.source);
        }
    }

    states: [
        State {
            name: "Pressed"
            when: mouseArea.pressed

            PropertyChanges {
                target: component
                color: "#3876ec"
            }

            PropertyChanges {
                target: text1
                color: "#deffffff"
            }

            PropertyChanges {
                target: text2
                color: "#deffffff"
            }
        }
    ]

}
